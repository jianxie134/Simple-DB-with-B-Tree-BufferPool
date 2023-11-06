#include <db/IndexPredicate.h>

using namespace db;

// TODO pa2.2: implement
IndexPredicate::IndexPredicate(Op op, const Field *fvalue) :op(op), fvalue(fvalue) {
}

// TODO pa2.2: implement
const Field *IndexPredicate::getField() const {
    return fvalue;
}

// TODO pa2.2: implement
Op IndexPredicate::getOp() const {
    return op;
}

// TODO pa2.2: implement
bool IndexPredicate::operator==(const IndexPredicate &other) const {
    return (op == other.getOp()) && fvalue->compare(Op::EQUALS, other.getField());
}

// TODO pa2.2: implement
std::size_t std::hash<IndexPredicate>::operator()(const IndexPredicate &ipd) const {
    return std::hash<const Field*>{}(ipd.getField()) ^ (std::hash<int>{}(static_cast<int>(ipd.getOp())) << 1);
}
