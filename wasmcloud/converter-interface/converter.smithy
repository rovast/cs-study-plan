// converter.smithy
//

// Tell the code generator how to reference symbols defined in this namespace
metadata package = [ { namespace: "org.example.interfaces.converter", crate: "converter_interface" } ]

namespace org.example.interfaces.converter

use org.wasmcloud.model#wasmbus

/// Description of Converter service
@wasmbus( actorReceive: true )
service Converter {
  version: "0.1",
  operations: [ Convert ]
}

/// Converts the input string to a result
operation Convert {
  input: String,
  output: String
}

