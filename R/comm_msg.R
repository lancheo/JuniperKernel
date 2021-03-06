# Copyright (C) 2017  Spencer Aiello
#
# This file is part of JuniperKernel.
#
# JuniperKernel is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# JuniperKernel is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with JuniperKernel.  If not, see <http://www.gnu.org/licenses/>.

#' Handler for the comm_msg Message Type
#'
#' @title Comm Msg
#' @param request_msg
#'   A list passed in from \code{doRequest} representing the
#'   deserialized \code{comm_msg} message JSON.
#'
#' @return NULL
#'
#' @author Spencer Aiello
#' @references \url{http://jupyter-client.readthedocs.io/en/latest/messaging.html#comm-messages}
#'
#' @examples
#' \dontrun{
#'   request_msg <- list("comm_id"="my_open_comm_id", "data"=list())
#'   comm_request(request_msg)
#' }
#'
#' @export
comm_msg <- function(request_msg) {
  comm_request("msg")
  NULL
}
