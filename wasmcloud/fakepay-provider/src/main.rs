//! fakepay-provider capability provider
//!
//!
use wasmbus_rpc::provider::prelude::*;
use wasmcloud_interface_factorial::{Factorial, FactorialReceiver};

// main (via provider_main) initializes the threaded tokio executor,
// listens to lattice rpcs, handles actor links,
// and returns only when it receives a shutdown message
//
fn main() -> Result<(), Box<dyn std::error::Error>> {
    provider_main(FakepayProviderProvider::default(), Some("FakepayProvider".to_string()))?;

    eprintln!("fakepay-provider provider exiting");
    Ok(())
}

/// fakepay-provider capability provider implementation
#[derive(Default, Clone, Provider)]
#[services(Factorial)]
struct FakepayProviderProvider {}

/// use default implementations of provider message handlers
impl ProviderDispatch for FakepayProviderProvider {}
impl ProviderHandler for FakepayProviderProvider {}

/// Handle Factorial methods
#[async_trait]
impl Factorial for FakepayProviderProvider {
    /// accepts a number and calculates its factorial
    async fn calculate(&self, _ctx: &Context, req: &u32) -> RpcResult<u64> {
        debug!("processing request calculate ({})", *req);
        Ok(n_factorial(*req))
    }
}

/// calculate n factorial
fn n_factorial(n: u32) -> u64 {
    match n {
        0 => 1,
        1 => 1,
        _ => {
            let mut result = 1u64;
            // add 1 because rust ranges exclude upper bound
            for v in 2..(n + 1) {
                result *= v as u64;
            }
            result
        }
    }
}
