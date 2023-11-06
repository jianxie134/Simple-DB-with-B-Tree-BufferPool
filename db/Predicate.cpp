#include <db/Predicate.h>

using namespace db;

// TODO pa2.2: implement
Predicate::Predicate(int field, Op op, const Field *operand) : field(field), op(op), operand(operand) {}

// TODO pa2.2: implement
int Predicate::getField() const {
    return field;
}

// TODO pa2.2: implement
Op Predicate::getOp() const {
    return op;
}

// TODO pa2.2: implement
const Field *Predicate::getOperand() const {
    return operand;
}

// TODO pa2.2: implement
bool Predicate::filter(const Tuple &t) const {
    const Field& f = t.getField(field);
    return f.compare(op, operand);
}
