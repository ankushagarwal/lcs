#pragma once
#include "serde.hpp"

struct Ed25519PublicKey {
    std::vector<uint8_t> value;
    friend bool operator==(const Ed25519PublicKey&, const Ed25519PublicKey&);
};

struct Ed25519Signature {
    std::vector<uint8_t> value;
    friend bool operator==(const Ed25519Signature&, const Ed25519Signature&);
};

struct MultiEd25519PublicKey {
    std::vector<uint8_t> value;
    friend bool operator==(const MultiEd25519PublicKey&, const MultiEd25519PublicKey&);
};

struct MultiEd25519Signature {
    std::vector<uint8_t> value;
    friend bool operator==(const MultiEd25519Signature&, const MultiEd25519Signature&);
};

struct TransactionAuthenticator {
    struct Ed25519 {
        ::Ed25519PublicKey public_key;
        ::Ed25519Signature signature;
        friend bool operator==(const Ed25519&, const Ed25519&);
    };
    struct MultiEd25519 {
        ::MultiEd25519PublicKey public_key;
        ::MultiEd25519Signature signature;
        friend bool operator==(const MultiEd25519&, const MultiEd25519&);
    };
    std::variant<Ed25519, MultiEd25519> value;
    friend bool operator==(const TransactionAuthenticator&, const TransactionAuthenticator&);
};

struct AccountAddress {
    std::array<uint8_t, 16> value;
    friend bool operator==(const AccountAddress&, const AccountAddress&);
};

struct Identifier {
    std::string value;
    friend bool operator==(const Identifier&, const Identifier&);
};

struct StructTag;

struct TypeTag;

struct TypeTag {
    struct Bool {
        friend bool operator==(const Bool&, const Bool&);
    };
    struct U8 {
        friend bool operator==(const U8&, const U8&);
    };
    struct U64 {
        friend bool operator==(const U64&, const U64&);
    };
    struct U128 {
        friend bool operator==(const U128&, const U128&);
    };
    struct Address {
        friend bool operator==(const Address&, const Address&);
    };
    struct Signer {
        friend bool operator==(const Signer&, const Signer&);
    };
    struct Vector {
        std::unique_ptr<::TypeTag> value;
        friend bool operator==(const Vector&, const Vector&);
    };
    struct Struct {
        std::unique_ptr<::StructTag> value;
        friend bool operator==(const Struct&, const Struct&);
    };
    std::variant<Bool, U8, U64, U128, Address, Signer, Vector, Struct> value;
    friend bool operator==(const TypeTag&, const TypeTag&);
};

struct StructTag {
    AccountAddress address;
    Identifier module;
    Identifier name;
    std::vector<TypeTag> type_params;
    friend bool operator==(const StructTag&, const StructTag&);
};

struct HashValue {
    std::vector<uint8_t> value;
    friend bool operator==(const HashValue&, const HashValue&);
};

struct BlockMetadata {
    HashValue id;
    uint64_t round;
    uint64_t timestamp_usecs;
    std::vector<AccountAddress> previous_block_votes;
    AccountAddress proposer;
    friend bool operator==(const BlockMetadata&, const BlockMetadata&);
};

struct EventKey {
    std::vector<uint8_t> value;
    friend bool operator==(const EventKey&, const EventKey&);
};

struct ContractEventV0 {
    EventKey key;
    uint64_t sequence_number;
    TypeTag type_tag;
    std::vector<uint8_t> event_data;
    friend bool operator==(const ContractEventV0&, const ContractEventV0&);
};

struct ContractEvent {
    struct V0 {
        ::ContractEventV0 value;
        friend bool operator==(const V0&, const V0&);
    };
    std::variant<V0> value;
    friend bool operator==(const ContractEvent&, const ContractEvent&);
};

struct AccessPath {
    AccountAddress address;
    std::vector<uint8_t> path;
    friend bool operator==(const AccessPath&, const AccessPath&);
};

struct WriteOp {
    struct Deletion {
        friend bool operator==(const Deletion&, const Deletion&);
    };
    struct Value {
        std::vector<uint8_t> value;
        friend bool operator==(const Value&, const Value&);
    };
    std::variant<Deletion, Value> value;
    friend bool operator==(const WriteOp&, const WriteOp&);
};

struct WriteSetMut {
    std::vector<std::tuple<AccessPath, WriteOp>> write_set;
    friend bool operator==(const WriteSetMut&, const WriteSetMut&);
};

struct WriteSet {
    WriteSetMut value;
    friend bool operator==(const WriteSet&, const WriteSet&);
};

struct ChangeSet {
    WriteSet write_set;
    std::vector<ContractEvent> events;
    friend bool operator==(const ChangeSet&, const ChangeSet&);
};

struct Module {
    std::vector<uint8_t> code;
    friend bool operator==(const Module&, const Module&);
};

struct TransactionArgument {
    struct U8 {
        uint8_t value;
        friend bool operator==(const U8&, const U8&);
    };
    struct U64 {
        uint64_t value;
        friend bool operator==(const U64&, const U64&);
    };
    struct U128 {
        uint128_t value;
        friend bool operator==(const U128&, const U128&);
    };
    struct Address {
        ::AccountAddress value;
        friend bool operator==(const Address&, const Address&);
    };
    struct U8Vector {
        std::vector<uint8_t> value;
        friend bool operator==(const U8Vector&, const U8Vector&);
    };
    struct Bool {
        bool value;
        friend bool operator==(const Bool&, const Bool&);
    };
    std::variant<U8, U64, U128, Address, U8Vector, Bool> value;
    friend bool operator==(const TransactionArgument&, const TransactionArgument&);
};

struct Script {
    std::vector<uint8_t> code;
    std::vector<TypeTag> ty_args;
    std::vector<TransactionArgument> args;
    friend bool operator==(const Script&, const Script&);
};

struct TransactionPayload {
    struct WriteSet {
        ::ChangeSet value;
        friend bool operator==(const WriteSet&, const WriteSet&);
    };
    struct Script {
        ::Script value;
        friend bool operator==(const Script&, const Script&);
    };
    struct Module {
        ::Module value;
        friend bool operator==(const Module&, const Module&);
    };
    std::variant<WriteSet, Script, Module> value;
    friend bool operator==(const TransactionPayload&, const TransactionPayload&);
};

struct RawTransaction {
    AccountAddress sender;
    uint64_t sequence_number;
    TransactionPayload payload;
    uint64_t max_gas_amount;
    uint64_t gas_unit_price;
    std::string gas_currency_code;
    uint64_t expiration_time;
    friend bool operator==(const RawTransaction&, const RawTransaction&);
};

struct SignedTransaction {
    RawTransaction raw_txn;
    TransactionAuthenticator authenticator;
    friend bool operator==(const SignedTransaction&, const SignedTransaction&);
};

struct Transaction {
    struct UserTransaction {
        ::SignedTransaction value;
        friend bool operator==(const UserTransaction&, const UserTransaction&);
    };
    struct WaypointWriteSet {
        ::ChangeSet value;
        friend bool operator==(const WaypointWriteSet&, const WaypointWriteSet&);
    };
    struct BlockMetadata {
        ::BlockMetadata value;
        friend bool operator==(const BlockMetadata&, const BlockMetadata&);
    };
    std::variant<UserTransaction, WaypointWriteSet, BlockMetadata> value;
    friend bool operator==(const Transaction&, const Transaction&);
};


bool operator==(const AccessPath &lhs, const AccessPath &rhs) {
    if (!(lhs.address == rhs.address)) { return false; }
    if (!(lhs.path == rhs.path)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<AccessPath>::serialize(const AccessPath &obj, Serializer &serializer) {
    Serializable<decltype(obj.address)>::serialize(obj.address, serializer);
    Serializable<decltype(obj.path)>::serialize(obj.path, serializer);
}

template <>
template <typename Deserializer>
AccessPath Deserializable<AccessPath>::deserialize(Deserializer &deserializer) {
    AccessPath obj;
    obj.address = Deserializable<decltype(obj.address)>::deserialize(deserializer);
    obj.path = Deserializable<decltype(obj.path)>::deserialize(deserializer);
    return obj;
}
bool operator==(const AccountAddress &lhs, const AccountAddress &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<AccountAddress>::serialize(const AccountAddress &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
AccountAddress Deserializable<AccountAddress>::deserialize(Deserializer &deserializer) {
    AccountAddress obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const BlockMetadata &lhs, const BlockMetadata &rhs) {
    if (!(lhs.id == rhs.id)) { return false; }
    if (!(lhs.round == rhs.round)) { return false; }
    if (!(lhs.timestamp_usecs == rhs.timestamp_usecs)) { return false; }
    if (!(lhs.previous_block_votes == rhs.previous_block_votes)) { return false; }
    if (!(lhs.proposer == rhs.proposer)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<BlockMetadata>::serialize(const BlockMetadata &obj, Serializer &serializer) {
    Serializable<decltype(obj.id)>::serialize(obj.id, serializer);
    Serializable<decltype(obj.round)>::serialize(obj.round, serializer);
    Serializable<decltype(obj.timestamp_usecs)>::serialize(obj.timestamp_usecs, serializer);
    Serializable<decltype(obj.previous_block_votes)>::serialize(obj.previous_block_votes, serializer);
    Serializable<decltype(obj.proposer)>::serialize(obj.proposer, serializer);
}

template <>
template <typename Deserializer>
BlockMetadata Deserializable<BlockMetadata>::deserialize(Deserializer &deserializer) {
    BlockMetadata obj;
    obj.id = Deserializable<decltype(obj.id)>::deserialize(deserializer);
    obj.round = Deserializable<decltype(obj.round)>::deserialize(deserializer);
    obj.timestamp_usecs = Deserializable<decltype(obj.timestamp_usecs)>::deserialize(deserializer);
    obj.previous_block_votes = Deserializable<decltype(obj.previous_block_votes)>::deserialize(deserializer);
    obj.proposer = Deserializable<decltype(obj.proposer)>::deserialize(deserializer);
    return obj;
}
bool operator==(const ChangeSet &lhs, const ChangeSet &rhs) {
    if (!(lhs.write_set == rhs.write_set)) { return false; }
    if (!(lhs.events == rhs.events)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<ChangeSet>::serialize(const ChangeSet &obj, Serializer &serializer) {
    Serializable<decltype(obj.write_set)>::serialize(obj.write_set, serializer);
    Serializable<decltype(obj.events)>::serialize(obj.events, serializer);
}

template <>
template <typename Deserializer>
ChangeSet Deserializable<ChangeSet>::deserialize(Deserializer &deserializer) {
    ChangeSet obj;
    obj.write_set = Deserializable<decltype(obj.write_set)>::deserialize(deserializer);
    obj.events = Deserializable<decltype(obj.events)>::deserialize(deserializer);
    return obj;
}
bool operator==(const ContractEvent &lhs, const ContractEvent &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<ContractEvent>::serialize(const ContractEvent &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
ContractEvent Deserializable<ContractEvent>::deserialize(Deserializer &deserializer) {
    ContractEvent obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const ContractEvent::V0 &lhs, const ContractEvent::V0 &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<ContractEvent::V0>::serialize(const ContractEvent::V0 &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
ContractEvent::V0 Deserializable<ContractEvent::V0>::deserialize(Deserializer &deserializer) {
    ContractEvent::V0 obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const ContractEventV0 &lhs, const ContractEventV0 &rhs) {
    if (!(lhs.key == rhs.key)) { return false; }
    if (!(lhs.sequence_number == rhs.sequence_number)) { return false; }
    if (!(lhs.type_tag == rhs.type_tag)) { return false; }
    if (!(lhs.event_data == rhs.event_data)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<ContractEventV0>::serialize(const ContractEventV0 &obj, Serializer &serializer) {
    Serializable<decltype(obj.key)>::serialize(obj.key, serializer);
    Serializable<decltype(obj.sequence_number)>::serialize(obj.sequence_number, serializer);
    Serializable<decltype(obj.type_tag)>::serialize(obj.type_tag, serializer);
    Serializable<decltype(obj.event_data)>::serialize(obj.event_data, serializer);
}

template <>
template <typename Deserializer>
ContractEventV0 Deserializable<ContractEventV0>::deserialize(Deserializer &deserializer) {
    ContractEventV0 obj;
    obj.key = Deserializable<decltype(obj.key)>::deserialize(deserializer);
    obj.sequence_number = Deserializable<decltype(obj.sequence_number)>::deserialize(deserializer);
    obj.type_tag = Deserializable<decltype(obj.type_tag)>::deserialize(deserializer);
    obj.event_data = Deserializable<decltype(obj.event_data)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Ed25519PublicKey &lhs, const Ed25519PublicKey &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Ed25519PublicKey>::serialize(const Ed25519PublicKey &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
Ed25519PublicKey Deserializable<Ed25519PublicKey>::deserialize(Deserializer &deserializer) {
    Ed25519PublicKey obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Ed25519Signature &lhs, const Ed25519Signature &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Ed25519Signature>::serialize(const Ed25519Signature &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
Ed25519Signature Deserializable<Ed25519Signature>::deserialize(Deserializer &deserializer) {
    Ed25519Signature obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const EventKey &lhs, const EventKey &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<EventKey>::serialize(const EventKey &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
EventKey Deserializable<EventKey>::deserialize(Deserializer &deserializer) {
    EventKey obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const HashValue &lhs, const HashValue &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<HashValue>::serialize(const HashValue &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
HashValue Deserializable<HashValue>::deserialize(Deserializer &deserializer) {
    HashValue obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Identifier &lhs, const Identifier &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Identifier>::serialize(const Identifier &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
Identifier Deserializable<Identifier>::deserialize(Deserializer &deserializer) {
    Identifier obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Module &lhs, const Module &rhs) {
    if (!(lhs.code == rhs.code)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Module>::serialize(const Module &obj, Serializer &serializer) {
    Serializable<decltype(obj.code)>::serialize(obj.code, serializer);
}

template <>
template <typename Deserializer>
Module Deserializable<Module>::deserialize(Deserializer &deserializer) {
    Module obj;
    obj.code = Deserializable<decltype(obj.code)>::deserialize(deserializer);
    return obj;
}
bool operator==(const MultiEd25519PublicKey &lhs, const MultiEd25519PublicKey &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<MultiEd25519PublicKey>::serialize(const MultiEd25519PublicKey &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
MultiEd25519PublicKey Deserializable<MultiEd25519PublicKey>::deserialize(Deserializer &deserializer) {
    MultiEd25519PublicKey obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const MultiEd25519Signature &lhs, const MultiEd25519Signature &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<MultiEd25519Signature>::serialize(const MultiEd25519Signature &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
MultiEd25519Signature Deserializable<MultiEd25519Signature>::deserialize(Deserializer &deserializer) {
    MultiEd25519Signature obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const RawTransaction &lhs, const RawTransaction &rhs) {
    if (!(lhs.sender == rhs.sender)) { return false; }
    if (!(lhs.sequence_number == rhs.sequence_number)) { return false; }
    if (!(lhs.payload == rhs.payload)) { return false; }
    if (!(lhs.max_gas_amount == rhs.max_gas_amount)) { return false; }
    if (!(lhs.gas_unit_price == rhs.gas_unit_price)) { return false; }
    if (!(lhs.gas_currency_code == rhs.gas_currency_code)) { return false; }
    if (!(lhs.expiration_time == rhs.expiration_time)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<RawTransaction>::serialize(const RawTransaction &obj, Serializer &serializer) {
    Serializable<decltype(obj.sender)>::serialize(obj.sender, serializer);
    Serializable<decltype(obj.sequence_number)>::serialize(obj.sequence_number, serializer);
    Serializable<decltype(obj.payload)>::serialize(obj.payload, serializer);
    Serializable<decltype(obj.max_gas_amount)>::serialize(obj.max_gas_amount, serializer);
    Serializable<decltype(obj.gas_unit_price)>::serialize(obj.gas_unit_price, serializer);
    Serializable<decltype(obj.gas_currency_code)>::serialize(obj.gas_currency_code, serializer);
    Serializable<decltype(obj.expiration_time)>::serialize(obj.expiration_time, serializer);
}

template <>
template <typename Deserializer>
RawTransaction Deserializable<RawTransaction>::deserialize(Deserializer &deserializer) {
    RawTransaction obj;
    obj.sender = Deserializable<decltype(obj.sender)>::deserialize(deserializer);
    obj.sequence_number = Deserializable<decltype(obj.sequence_number)>::deserialize(deserializer);
    obj.payload = Deserializable<decltype(obj.payload)>::deserialize(deserializer);
    obj.max_gas_amount = Deserializable<decltype(obj.max_gas_amount)>::deserialize(deserializer);
    obj.gas_unit_price = Deserializable<decltype(obj.gas_unit_price)>::deserialize(deserializer);
    obj.gas_currency_code = Deserializable<decltype(obj.gas_currency_code)>::deserialize(deserializer);
    obj.expiration_time = Deserializable<decltype(obj.expiration_time)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Script &lhs, const Script &rhs) {
    if (!(lhs.code == rhs.code)) { return false; }
    if (!(lhs.ty_args == rhs.ty_args)) { return false; }
    if (!(lhs.args == rhs.args)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Script>::serialize(const Script &obj, Serializer &serializer) {
    Serializable<decltype(obj.code)>::serialize(obj.code, serializer);
    Serializable<decltype(obj.ty_args)>::serialize(obj.ty_args, serializer);
    Serializable<decltype(obj.args)>::serialize(obj.args, serializer);
}

template <>
template <typename Deserializer>
Script Deserializable<Script>::deserialize(Deserializer &deserializer) {
    Script obj;
    obj.code = Deserializable<decltype(obj.code)>::deserialize(deserializer);
    obj.ty_args = Deserializable<decltype(obj.ty_args)>::deserialize(deserializer);
    obj.args = Deserializable<decltype(obj.args)>::deserialize(deserializer);
    return obj;
}
bool operator==(const SignedTransaction &lhs, const SignedTransaction &rhs) {
    if (!(lhs.raw_txn == rhs.raw_txn)) { return false; }
    if (!(lhs.authenticator == rhs.authenticator)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<SignedTransaction>::serialize(const SignedTransaction &obj, Serializer &serializer) {
    Serializable<decltype(obj.raw_txn)>::serialize(obj.raw_txn, serializer);
    Serializable<decltype(obj.authenticator)>::serialize(obj.authenticator, serializer);
}

template <>
template <typename Deserializer>
SignedTransaction Deserializable<SignedTransaction>::deserialize(Deserializer &deserializer) {
    SignedTransaction obj;
    obj.raw_txn = Deserializable<decltype(obj.raw_txn)>::deserialize(deserializer);
    obj.authenticator = Deserializable<decltype(obj.authenticator)>::deserialize(deserializer);
    return obj;
}
bool operator==(const StructTag &lhs, const StructTag &rhs) {
    if (!(lhs.address == rhs.address)) { return false; }
    if (!(lhs.module == rhs.module)) { return false; }
    if (!(lhs.name == rhs.name)) { return false; }
    if (!(lhs.type_params == rhs.type_params)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<StructTag>::serialize(const StructTag &obj, Serializer &serializer) {
    Serializable<decltype(obj.address)>::serialize(obj.address, serializer);
    Serializable<decltype(obj.module)>::serialize(obj.module, serializer);
    Serializable<decltype(obj.name)>::serialize(obj.name, serializer);
    Serializable<decltype(obj.type_params)>::serialize(obj.type_params, serializer);
}

template <>
template <typename Deserializer>
StructTag Deserializable<StructTag>::deserialize(Deserializer &deserializer) {
    StructTag obj;
    obj.address = Deserializable<decltype(obj.address)>::deserialize(deserializer);
    obj.module = Deserializable<decltype(obj.module)>::deserialize(deserializer);
    obj.name = Deserializable<decltype(obj.name)>::deserialize(deserializer);
    obj.type_params = Deserializable<decltype(obj.type_params)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Transaction &lhs, const Transaction &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Transaction>::serialize(const Transaction &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
Transaction Deserializable<Transaction>::deserialize(Deserializer &deserializer) {
    Transaction obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Transaction::UserTransaction &lhs, const Transaction::UserTransaction &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Transaction::UserTransaction>::serialize(const Transaction::UserTransaction &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
Transaction::UserTransaction Deserializable<Transaction::UserTransaction>::deserialize(Deserializer &deserializer) {
    Transaction::UserTransaction obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Transaction::WaypointWriteSet &lhs, const Transaction::WaypointWriteSet &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Transaction::WaypointWriteSet>::serialize(const Transaction::WaypointWriteSet &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
Transaction::WaypointWriteSet Deserializable<Transaction::WaypointWriteSet>::deserialize(Deserializer &deserializer) {
    Transaction::WaypointWriteSet obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const Transaction::BlockMetadata &lhs, const Transaction::BlockMetadata &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<Transaction::BlockMetadata>::serialize(const Transaction::BlockMetadata &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
Transaction::BlockMetadata Deserializable<Transaction::BlockMetadata>::deserialize(Deserializer &deserializer) {
    Transaction::BlockMetadata obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionArgument &lhs, const TransactionArgument &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionArgument>::serialize(const TransactionArgument &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionArgument Deserializable<TransactionArgument>::deserialize(Deserializer &deserializer) {
    TransactionArgument obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionArgument::U8 &lhs, const TransactionArgument::U8 &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionArgument::U8>::serialize(const TransactionArgument::U8 &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionArgument::U8 Deserializable<TransactionArgument::U8>::deserialize(Deserializer &deserializer) {
    TransactionArgument::U8 obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionArgument::U64 &lhs, const TransactionArgument::U64 &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionArgument::U64>::serialize(const TransactionArgument::U64 &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionArgument::U64 Deserializable<TransactionArgument::U64>::deserialize(Deserializer &deserializer) {
    TransactionArgument::U64 obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionArgument::U128 &lhs, const TransactionArgument::U128 &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionArgument::U128>::serialize(const TransactionArgument::U128 &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionArgument::U128 Deserializable<TransactionArgument::U128>::deserialize(Deserializer &deserializer) {
    TransactionArgument::U128 obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionArgument::Address &lhs, const TransactionArgument::Address &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionArgument::Address>::serialize(const TransactionArgument::Address &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionArgument::Address Deserializable<TransactionArgument::Address>::deserialize(Deserializer &deserializer) {
    TransactionArgument::Address obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionArgument::U8Vector &lhs, const TransactionArgument::U8Vector &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionArgument::U8Vector>::serialize(const TransactionArgument::U8Vector &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionArgument::U8Vector Deserializable<TransactionArgument::U8Vector>::deserialize(Deserializer &deserializer) {
    TransactionArgument::U8Vector obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionArgument::Bool &lhs, const TransactionArgument::Bool &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionArgument::Bool>::serialize(const TransactionArgument::Bool &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionArgument::Bool Deserializable<TransactionArgument::Bool>::deserialize(Deserializer &deserializer) {
    TransactionArgument::Bool obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionAuthenticator &lhs, const TransactionAuthenticator &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionAuthenticator>::serialize(const TransactionAuthenticator &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionAuthenticator Deserializable<TransactionAuthenticator>::deserialize(Deserializer &deserializer) {
    TransactionAuthenticator obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionAuthenticator::Ed25519 &lhs, const TransactionAuthenticator::Ed25519 &rhs) {
    if (!(lhs.public_key == rhs.public_key)) { return false; }
    if (!(lhs.signature == rhs.signature)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionAuthenticator::Ed25519>::serialize(const TransactionAuthenticator::Ed25519 &obj, Serializer &serializer) {
    Serializable<decltype(obj.public_key)>::serialize(obj.public_key, serializer);
    Serializable<decltype(obj.signature)>::serialize(obj.signature, serializer);
}

template <>
template <typename Deserializer>
TransactionAuthenticator::Ed25519 Deserializable<TransactionAuthenticator::Ed25519>::deserialize(Deserializer &deserializer) {
    TransactionAuthenticator::Ed25519 obj;
    obj.public_key = Deserializable<decltype(obj.public_key)>::deserialize(deserializer);
    obj.signature = Deserializable<decltype(obj.signature)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionAuthenticator::MultiEd25519 &lhs, const TransactionAuthenticator::MultiEd25519 &rhs) {
    if (!(lhs.public_key == rhs.public_key)) { return false; }
    if (!(lhs.signature == rhs.signature)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionAuthenticator::MultiEd25519>::serialize(const TransactionAuthenticator::MultiEd25519 &obj, Serializer &serializer) {
    Serializable<decltype(obj.public_key)>::serialize(obj.public_key, serializer);
    Serializable<decltype(obj.signature)>::serialize(obj.signature, serializer);
}

template <>
template <typename Deserializer>
TransactionAuthenticator::MultiEd25519 Deserializable<TransactionAuthenticator::MultiEd25519>::deserialize(Deserializer &deserializer) {
    TransactionAuthenticator::MultiEd25519 obj;
    obj.public_key = Deserializable<decltype(obj.public_key)>::deserialize(deserializer);
    obj.signature = Deserializable<decltype(obj.signature)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionPayload &lhs, const TransactionPayload &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionPayload>::serialize(const TransactionPayload &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionPayload Deserializable<TransactionPayload>::deserialize(Deserializer &deserializer) {
    TransactionPayload obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionPayload::WriteSet &lhs, const TransactionPayload::WriteSet &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionPayload::WriteSet>::serialize(const TransactionPayload::WriteSet &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionPayload::WriteSet Deserializable<TransactionPayload::WriteSet>::deserialize(Deserializer &deserializer) {
    TransactionPayload::WriteSet obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionPayload::Script &lhs, const TransactionPayload::Script &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionPayload::Script>::serialize(const TransactionPayload::Script &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionPayload::Script Deserializable<TransactionPayload::Script>::deserialize(Deserializer &deserializer) {
    TransactionPayload::Script obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TransactionPayload::Module &lhs, const TransactionPayload::Module &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TransactionPayload::Module>::serialize(const TransactionPayload::Module &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TransactionPayload::Module Deserializable<TransactionPayload::Module>::deserialize(Deserializer &deserializer) {
    TransactionPayload::Module obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TypeTag &lhs, const TypeTag &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag>::serialize(const TypeTag &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TypeTag Deserializable<TypeTag>::deserialize(Deserializer &deserializer) {
    TypeTag obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TypeTag::Bool &lhs, const TypeTag::Bool &rhs) {
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::Bool>::serialize(const TypeTag::Bool &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
TypeTag::Bool Deserializable<TypeTag::Bool>::deserialize(Deserializer &deserializer) {
    TypeTag::Bool obj;
    return obj;
}
bool operator==(const TypeTag::U8 &lhs, const TypeTag::U8 &rhs) {
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::U8>::serialize(const TypeTag::U8 &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
TypeTag::U8 Deserializable<TypeTag::U8>::deserialize(Deserializer &deserializer) {
    TypeTag::U8 obj;
    return obj;
}
bool operator==(const TypeTag::U64 &lhs, const TypeTag::U64 &rhs) {
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::U64>::serialize(const TypeTag::U64 &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
TypeTag::U64 Deserializable<TypeTag::U64>::deserialize(Deserializer &deserializer) {
    TypeTag::U64 obj;
    return obj;
}
bool operator==(const TypeTag::U128 &lhs, const TypeTag::U128 &rhs) {
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::U128>::serialize(const TypeTag::U128 &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
TypeTag::U128 Deserializable<TypeTag::U128>::deserialize(Deserializer &deserializer) {
    TypeTag::U128 obj;
    return obj;
}
bool operator==(const TypeTag::Address &lhs, const TypeTag::Address &rhs) {
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::Address>::serialize(const TypeTag::Address &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
TypeTag::Address Deserializable<TypeTag::Address>::deserialize(Deserializer &deserializer) {
    TypeTag::Address obj;
    return obj;
}
bool operator==(const TypeTag::Signer &lhs, const TypeTag::Signer &rhs) {
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::Signer>::serialize(const TypeTag::Signer &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
TypeTag::Signer Deserializable<TypeTag::Signer>::deserialize(Deserializer &deserializer) {
    TypeTag::Signer obj;
    return obj;
}
bool operator==(const TypeTag::Vector &lhs, const TypeTag::Vector &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::Vector>::serialize(const TypeTag::Vector &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TypeTag::Vector Deserializable<TypeTag::Vector>::deserialize(Deserializer &deserializer) {
    TypeTag::Vector obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const TypeTag::Struct &lhs, const TypeTag::Struct &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<TypeTag::Struct>::serialize(const TypeTag::Struct &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
TypeTag::Struct Deserializable<TypeTag::Struct>::deserialize(Deserializer &deserializer) {
    TypeTag::Struct obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const WriteOp &lhs, const WriteOp &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<WriteOp>::serialize(const WriteOp &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
WriteOp Deserializable<WriteOp>::deserialize(Deserializer &deserializer) {
    WriteOp obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const WriteOp::Deletion &lhs, const WriteOp::Deletion &rhs) {
    return true;
}

template <>
template <typename Serializer>
void Serializable<WriteOp::Deletion>::serialize(const WriteOp::Deletion &obj, Serializer &serializer) {
}

template <>
template <typename Deserializer>
WriteOp::Deletion Deserializable<WriteOp::Deletion>::deserialize(Deserializer &deserializer) {
    WriteOp::Deletion obj;
    return obj;
}
bool operator==(const WriteOp::Value &lhs, const WriteOp::Value &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<WriteOp::Value>::serialize(const WriteOp::Value &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
WriteOp::Value Deserializable<WriteOp::Value>::deserialize(Deserializer &deserializer) {
    WriteOp::Value obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const WriteSet &lhs, const WriteSet &rhs) {
    if (!(lhs.value == rhs.value)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<WriteSet>::serialize(const WriteSet &obj, Serializer &serializer) {
    Serializable<decltype(obj.value)>::serialize(obj.value, serializer);
}

template <>
template <typename Deserializer>
WriteSet Deserializable<WriteSet>::deserialize(Deserializer &deserializer) {
    WriteSet obj;
    obj.value = Deserializable<decltype(obj.value)>::deserialize(deserializer);
    return obj;
}
bool operator==(const WriteSetMut &lhs, const WriteSetMut &rhs) {
    if (!(lhs.write_set == rhs.write_set)) { return false; }
    return true;
}

template <>
template <typename Serializer>
void Serializable<WriteSetMut>::serialize(const WriteSetMut &obj, Serializer &serializer) {
    Serializable<decltype(obj.write_set)>::serialize(obj.write_set, serializer);
}

template <>
template <typename Deserializer>
WriteSetMut Deserializable<WriteSetMut>::deserialize(Deserializer &deserializer) {
    WriteSetMut obj;
    obj.write_set = Deserializable<decltype(obj.write_set)>::deserialize(deserializer);
    return obj;
}
