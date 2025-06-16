#include "MenuFunctions.h"

MenuFunctions::MenuFunctions() : 
    cli("localhost:3000"),
    studentOps(cli),
    subjectOps(cli),
    gradeOps(cli),
    analyticsOps(cli) {} 