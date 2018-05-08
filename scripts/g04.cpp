#include "header.h"

SCRIPT_ENTRY_POINT(ScriptContext &ctx,std::string arg) {
    unsigned long us=0;

    if (ctx.line().hasArg(1)) {
        std::string s=ctx.line().getArgAsString();
        char c=s.at(0);
        switch(c) {
            case 'P': us=1000000; break;
            case 'F': us=1000; break;
            default: us=0;
        }
        s.at(0)='0';
        int t=std::stoi(s);
        us=us*i;
        ctx.wait(us);
    }
    return 0;
}