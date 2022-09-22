// payments.smithy
// A simple service that calculates the factorial of a whole number


// Tell the code generator how to reference symbols defined in this namespace
metadata package = [ { namespace: "org.example.interfaces.payments", crate: "payments_interface" } ]

namespace org.example.interfaces.payments

use org.wasmcloud.model#wasmbus
use org.wasmcloud.model#U32
use org.wasmcloud.model#U64

/// The Payments service has a single method, calculate, which
/// calculates the factorial of its whole number parameter.
@wasmbus(
    contractId: "example:interfaces:payments",
    actorReceive: true,
    providerReceive: true )
service Payments {
  version: "0.1",
  operations: [ Calculate ]
}

/// Calculates the factorial (n!) of the input parameter
operation Calculate {
  input: U32,
  output: U64
}

