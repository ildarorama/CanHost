#include "header.h"

SCRIPT_ENTRY_POINT(ScriptContext &ctx,std::string arg) {

    ctx.log("%s %d %s", "it work",5," fewfew");

    ctx.wait(1000);
    if (ctx.hasAlias(arg)) {
        ctx.module()->alias(arg)->output(true);
    }

    ctx.log() << "TEST ME LOG";
    ctx.wait(2000);

    std::cout << "Receive done " << std::endl;
    return 0;
}