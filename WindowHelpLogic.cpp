#include "WindowHelpLogic.h"
WindowHelpLogic::WindowHelpLogic() {

}
void WindowHelpLogic::ViewAdjust(sf::RenderWindow& window) {
    sf::Vector2u window_Size_Resize = window.getSize();
    sf::View window_View = window.getView();
    sf::Vector2f f_WindowSize(
        static_cast<float>(window_Size_Resize.x),
        static_cast<float>(window_Size_Resize.y)
    );

    window_View.setSize(f_WindowSize);
    sf::Vector2f window_View_Center = {
        window_View.getSize().x / 2,
        window_View.getSize().y / 2
    };
    window_View.setCenter(window_View_Center);
    window.setView(window_View);
    std::cout << ' ' << f_WindowSize.x << ' ' << f_WindowSize.y;
}