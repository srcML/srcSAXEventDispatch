#include <srcSAXEventDispatch.hpp>
#include <srcSAXHandler.hpp>
#include <exception>
#include <unordered_map>
class TypePolicy : public srcSAXEventDispatch::Listener{
    struct TypeData{
        std::string nameoftype;
        std::string nameofidentifier;
        bool isConst;
        bool isReference;
        bool isPointer;
        bool isStatic;
    };
    public:
        TypeData data;
        ~TypePolicy(){}
        TypePolicy(){InitializeEventHandlers();}
        void HandleEvent(){}
    private:
        std::string currentTypeName, currentDeclName, currentModifier, currentSpecifier;
        std::unordered_map<srcSAXEventDispatch::ParserState, std::function<void(const srcSAXEventDispatch::srcSAXEventContext&)>, std::hash<int>> EventToHandlerMap;
        void HandleEvent(srcSAXEventDispatch::ParserState pstate, srcSAXEventDispatch::ElementState estate, const srcSAXEventDispatch::srcSAXEventContext& ctx) override{
            switch(estate){
                case srcSAXEventDispatch::ElementState::open:{
                    return; //do nothing
                }
                case srcSAXEventDispatch::ElementState::close:{
                    auto event = EventToHandlerMap.find(pstate);
                    if(event != EventToHandlerMap.end()){
                        event->second(ctx);
                    }
                    break;
                }
                default:
                    throw std::runtime_error("Something went terribly, terribly wrong"); 
            }
        }
        void InitializeEventHandlers(){
            using namespace srcSAXEventDispatch;
            EventToHandlerMap = {  
                { ParserState::modifier, [this](const srcSAXEventContext& ctx){
                    if(ctx.IsOpen(ParserState::declstmt)){
                        if(currentModifier == "*"){
                            data.isPointer = true;
                        }
                        else if(currentModifier == "&"){
                            data.isReference = true;
                        }
                    }
                } },    
                { ParserState::decl, [this](const srcSAXEventContext& ctx){
                    if(ctx.And({ParserState::declstmt})){
                        data.nameofidentifier = currentDeclName;
                    }
                } },    
                { ParserState::type, [this](const srcSAXEventContext& ctx){
                    if(ctx.And({ParserState::declstmt})){
                        data.nameoftype = currentTypeName;
                    }
                } },
                { ParserState::tokenstring, [this](const srcSAXEventContext& ctx){
                    if(!(ctx.currentToken.empty() || ctx.currentToken[0] == ' ')){
                        if(ctx.And({ParserState::name, ParserState::type, ParserState::decl, ParserState::declstmt}) && ctx.Nor({ParserState::specifier, ParserState::modifier}) && !ctx.sawgeneric){
                            currentTypeName = ctx.currentToken;
                        }
                        if(ctx.And({ParserState::name, ParserState::decl, ParserState::declstmt}) && 
                           ctx.Nor({ParserState::type, ParserState::index/*skip array portion*/, ParserState::argumentlist/*skip init list portion*/, ParserState::init, ParserState::specifier, ParserState::modifier}) && 
                           !ctx.sawgeneric){
                            currentDeclName = ctx.currentToken;
                        }
                        if(ctx.And({ParserState::specifier, ParserState::type, ParserState::declstmt})){
                            currentSpecifier = ctx.currentToken;
                        }
                        if(ctx.And({ParserState::modifier, ParserState::type, ParserState::declstmt})){
                            currentModifier = ctx.currentToken;
                        }
                    }
                } },
                { ParserState::specifier, [this](const srcSAXEventContext& ctx){
                    if(ctx.IsOpen(ParserState::declstmt)){
                        if(currentSpecifier == "const"){
                            data.isStatic = true;
                        }
                        else if(currentSpecifier == "static"){
                            data.isConst = true;
                        }
                    }
                } }
            };
        }
};