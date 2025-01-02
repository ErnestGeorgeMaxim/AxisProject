#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <utility>

class JsonValue {
public:
    virtual ~JsonValue() = 0;

    virtual void print(std::ostream& out, int indent = 0) const = 0;

    virtual unsigned countNodes() const = 0;

    operator unsigned() const {
        return countNodes();
    }

protected:
    void printIndent(std::ostream& out, int indent) const {
        for (int i = 0; i < indent; ++i) {
            out << "  ";
        }
    }
};

inline JsonValue::~JsonValue() {}

class NullValue : public JsonValue {
public:
    void print(std::ostream& out, int indent = 0) const override {
        out << "null";
    }

    unsigned countNodes() const override {
        return 1;
    }
};

class NumberValue : public JsonValue {
private:
    int value;
public:
    NumberValue(const int& value) : value(value) {}

    void print(std::ostream& out, int indent = 0) const override {
        out << value;
    }

    unsigned countNodes() const override {
        return 1;
    }
};

class BoolValue : public JsonValue {
private:
    bool value;
public:
    BoolValue(const bool& value) : value(value) {}

    void print(std::ostream& out, int indent = 0) const override {
        out << (value ? "true" : "false");
    }

    unsigned countNodes() const override {
        return 1;
    }
};

class StringValue : public JsonValue {
private:
    std::string value;
public:
    StringValue(const std::string& value) : value(value) {}

    void print(std::ostream& out, int indent = 0) const override {
        out << '"' << value << '"';
    }

    unsigned countNodes() const override {
        return 1;
    }
};

class ArrayValue : public JsonValue {
private:
    std::vector<JsonValue*> arr;
public:
    ~ArrayValue() {
        for (auto val : arr) {
            delete val;
        }
    }

    void add(JsonValue* jv) {
        if (arr.size() < 16) {
            arr.emplace_back(jv);
        }
    }

    void print(std::ostream& out, int indent = 0) const override {
        out << "[\n";
        for (size_t i = 0; i < arr.size(); ++i) {
            printIndent(out, indent + 1);
            arr[i]->print(out, indent + 1);
            if (i < arr.size() - 1) out << ",";
            out << "\n";
        }
        printIndent(out, indent);
        out << "]";
    }

    unsigned countNodes() const override {
        unsigned count = 1; // Counting this node
        for (auto val : arr) {
            count += val->countNodes();
        }
        return count;
    }
};

class ObjectValue : public JsonValue {
private:
    std::vector<std::pair<std::string, JsonValue*>> obarr;
public:
    ~ObjectValue() {
        for (auto& pair : obarr) {
            delete pair.second;
        }
    }

    void add(const std::string& name, JsonValue* jv) {
        if (obarr.size() < 16) {
            obarr.emplace_back(std::make_pair(name, jv));
        }
    }

    void print(std::ostream& out, int indent = 0) const override {
        out << "{\n";
        for (size_t i = 0; i < obarr.size(); ++i) {
            printIndent(out, indent + 1);
            out << '"' << obarr[i].first << "\": ";
            obarr[i].second->print(out, indent + 1);
            if (i < obarr.size() - 1) out << ",";
            out << "\n";
        }
        printIndent(out, indent);
        out << "}";
    }

    unsigned countNodes() const override {
        unsigned count = 1; // Counting this node
        for (auto& pair : obarr) {
            count += pair.second->countNodes();
        }
        return count;
    }
};

int main() {
    auto array_numbers = new ArrayValue();
    array_numbers->add(new NumberValue(5));
    array_numbers->add(new NumberValue(10));
    array_numbers->add(new NumberValue(15));

    auto array_strings = new ArrayValue();
    array_strings->add(new StringValue("abc"));
    array_strings->add(new StringValue("def"));
    array_strings->add(new StringValue("ghi"));

    auto subobject = new ObjectValue();
    subobject->add("email", new StringValue("t@gmail.com"));
    subobject->add("name", new StringValue("T"));
    subobject->add("online", new BoolValue(true));

    auto object = new ObjectValue();
    object->add("n", new NullValue());
    object->add("array_numbers", array_numbers);
    object->add("array_strings", array_strings);
    object->add("info", subobject);

    std::cout << "Top node has " << (unsigned)*object << " subnodes\n";

    object->print(std::cout);
    return 0;
}