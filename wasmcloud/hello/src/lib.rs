use wasmbus_rpc::actor::prelude::*;
use wasmcloud_interface_httpserver::{HttpRequest, HttpResponse, HttpServer, HttpServerReceiver};

// The HealthResponder term generates a function 
// that automatically responds to health check queries from the wasmCloud host. 
#[derive(Debug, Default, Actor, HealthResponder)]
// The #[services(...)] line declares the services (‘traits’, in Rust) that your actor implements, 
// and generates message handling code for those interfaces.
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
        handle_http_request(req)
    }
}

fn handle_http_request(req: &HttpRequest) -> std::result::Result<HttpResponse, RpcError> {
    let text = form_urlencoded::parse(req.query_string.as_bytes())
        .find(|(n, _)| n == "name")
        .map(|(_, v)| v.to_string())
        .unwrap_or_else(|| "World".to_string());

    Ok(HttpResponse {
        body: format!("Hello {}", text).as_bytes().to_vec(),
        ..Default::default()
    })
}

#[cfg(test)]
mod test {
    use crate::handle_http_request;
    use std::collections::HashMap;
    use wasmcloud_interface_httpserver::{HttpRequest, HttpResponse};

    #[test]
    fn can_handle_request() {
        let request = HttpRequest {
            method: "GET".to_string(),
            path: "/".to_string(),
            query_string: "name=test".to_string(),
            header: HashMap::new(),
            body: vec![],
        };

        let response: HttpResponse = handle_http_request(&request).unwrap();

        assert_eq!(response.status_code, 200);
        assert_eq!(
            String::from_utf8(response.body).unwrap(),
            "Hello test".to_string()
        );
    }
}
