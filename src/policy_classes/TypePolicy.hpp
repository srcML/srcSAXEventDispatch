#include <srcSAXEventDispatch.hpp>
#include <srcSAXHandler.hpp>

#include <SingleEventPolicyDispatcher.hpp>

#include <exception>

#ifndef INCLUDED_TYPE_POLICY_HPP
#define INCLUDED_TYPE_POLICY_HPP

class NamePolicy;
class TypePolicy : public srcSAXEventDispatch::EventListener, public srcSAXEventDispatch::PolicyDispatcher, public srcSAXEventDispatch::PolicyListener {

public:
    enum TypeType { NAME, POINTER, REFERENCE, RVALUE, SPECIFIER, NONE };

    struct TypeData {
        std::vector<std::pair<void *, TypeType>> types;

        friend std::ostream & operator<<(std::ostream & out, const TypeData & typeData);

    };
    private:
        TypeData data;
        std::size_t typeDepth;

        SingleEventPolicyDispatcher & policy_handler;
        NamePolicy * namePolicy;

    public:
        TypePolicy(SingleEventPolicyDispatcher & policy_handler, std::initializer_list<srcSAXEventDispatch::PolicyListener *> listeners);
        ~TypePolicy();
        virtual void Notify(const PolicyDispatcher * policy, const srcSAXEventDispatch::srcSAXEventContext & ctx) override;
    protected:
        virtual void * DataInner() const override;
    private:
        void InitializeTypePolicyHandlers();

        void CollectNamesHandler();
        void CollectModifersHandler();
        void CollectSpecifiersHandler();

};

#endif
