//
// Created by Da on 5/6/25.
//

#ifndef INTERFACE_MENU_ACTION_H
#define INTERFACE_MENU_ACTION_H

namespace menu {
    class IMenuAction {
    public:
        virtual ~IMenuAction() = default;

        virtual void login() = 0;
    };
}

#endif //INTERFACE_MENU_ACTION_H
