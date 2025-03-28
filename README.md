# Bount Core Module

The standard headers and libraries used throughout various bount systems.

# Features
## SVG Parser (port of [svgpp](https://github.com/svgpp/svgpp.git))
XML/SVG Parsing.

Header-only library.

## Networking Library (port of [boost.asio](https://github.com/boostorg/boost.git))
Create TCP Server/Client.

Create UDP Server/Client.

Send/Recv Packets.

# Standard
## Sized Datatypes:

Boolean
- `Bount::B8`, 8-bit Boolean (true or false)

Unsigned Integers
- `Bount::U8`, 8-bit Unsigned Integer (0 to 2^8 - 1)
- `Bount::U16`, 16-bit Unsigned Integer (0 to 2^16 - 1)
- `Bount::U32`, 32-bit Unsigned Integer (0 to 2^32 - 1)
- `Bount::U64`, 64-bit Unsigned Integer (0 to 2^64 - 1)

Signed Integers
- `Bount::I8`, 8-bit Signed Integer (-2^7 to 2^7 - 1)
- `Bount::I16`, 16-bit Signed Integer (-2^15 to 2^15 - 1)
- `Bount::I32`, 32-bit Signed Integer (-2^31 to 2^31 - 1)
- `Bount::I64`, 64-bit Signed Integer (-2^63 to 2^63 - 1)

Floating Points
- `Bount::F32`, 32-bit Floating Point
- `Bount::F64`, 64-bit Floating Point
- `Bount::FMaxT`, Largest Supported Floating Point

Characters
- `Bount::C8`, 8-bit Signed Character
- `Bount::UC8`, 8-bit Unsigned Character
- `Bount::UC16`, at least 16-bit Unsigned Character
- `Bount::UC32`, at least 32-bit Unsigned Character

## Alias Datatypes:
- `Bount::SizeT`, size_t alias
- `Bount::ByteT`, char alias