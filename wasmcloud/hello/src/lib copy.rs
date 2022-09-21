use wasmbus_rpc::actor::prelude::*;
use wasmcloud_interface_httpserver::{HttpRequest, HttpResponse, HttpServer, HttpServerReceiver};

#[derive(Debug, Default, Actor, HealthResponder)]
#[services(Actor, HttpServer)]
struct HelloActor {}

/// Implementation of HttpServer trait methods
#[async_trait]
impl HttpServer for HelloActor {
    /// Returns a greeting, "Hello World", in the response body.
    /// If the request contains a query parameter 'name=NAME', the
    /// response is changed to "Hello NAME"
    async fn handle_request(
        &self,
        _ctx: &Context,
        req: &HttpRequest,
    ) -> std::result::Result<HttpResponse, RpcError> {
        let name = form_urlencoded::parse(req.query_string.as_bytes())
            .find(|(n, _)| n == "name")
            .map(|(_, v)| v.to_string())
            .unwrap_or_else(|| "You".to_string());

        let msg_id = form_urlencoded::parse(req.query_string.as_bytes())
            .find(|(n, _)| n == "msg")
            .map(|(_, v)| v.to_string())
            .unwrap_or_else(|| "hello".to_string());

        let response = match msg_id.as_str() {
            "hello" => format!("Hello {}", name),
            "bye" => format!("Goodbye {}", name),
            "hey" => format!("Hey {}, what's up?", name),
            _ => format!("I didn't understand that, {}", name),
        };

        Ok(HttpResponse {
            body: response.as_bytes().to_vec(),
            ..Default::default()
        })
    }
}
