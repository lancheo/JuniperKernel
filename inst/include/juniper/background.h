#ifndef juniper_juniper_background_H
#define juniper_juniper_background_H

#include <string>
#include <thread>
#include <zmq.hpp>
#include <zmq_addon.hpp>
#include "sockets.h"


std::thread start_hb_thread(zmq::context_t& ctx, const std::string& endpoint) {
  std::thread hbthread([&ctx, endpoint]() {
    zmq::socket_t* hbSock = listen_on(ctx, endpoint, zmq::socket_type::rep);  // bind to the heartbeat endpoint
    std::function<bool()> handlers[] = {
      // ping-pong the message on heartbeat
      [&hbSock]() {
        zmq::multipart_t msg;
        msg.recv(*hbSock);
        msg.send(*hbSock);
        return true;
      }
    };
    poll(ctx, (zmq::socket_t*[]){hbSock}, handlers, 1);
  });
  return hbthread;
}

std::thread start_io_thread(zmq::context_t& ctx, const std::string& endpoint) {
  std::thread iothread([&ctx, endpoint]() {
    zmq::socket_t* io = listen_on(ctx, endpoint, zmq::socket_type::pub);  // bind to the iopub endpoint
    zmq::socket_t* pubsub = subscribe_to(ctx, INPROC_PUB); // subscription to internal publisher
    std::function<bool()> handlers[] = {
      // msg forwarding
      [&pubsub, &io]() {
        // we've got some messages to send from the
        // execution engine back to the client. Messages
        // from the executor are published to the inproc_pub
        // topic, and we forward them to the client here.
        zmq::multipart_t msg;
        msg.recv(*pubsub);
        msg.send(*io);
        return true;
      }
    };
    poll(ctx, (zmq::socket_t*[]){pubsub}, handlers, 1);
    io->setsockopt(ZMQ_LINGER, 0);
    delete io;
  });
  return iothread;
}

#endif // #ifndef juniper_juniper_background_H
