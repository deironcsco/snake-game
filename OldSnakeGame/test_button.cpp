#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


/*

    //start button bg
    float startbutton_bgx{ 150 };
    float startbutton_bgy{ 100 };
    sf::RectangleShape startbutton_bg({startbutton_bgx, startbutton_bgy});
    startbutton_bg.setFillColor(green);
    startbutton_bg.setOutlineColor(black);
    startbutton_bg.setOutlineThickness(outline_thickness);
    startbutton_bg.setOrigin({startbutton_bgx/2, startbutton_bgy/2}); //half of its dimensions
    startbutton_bg.setPosition(button_position);
    
    //start button text
    float startbutton_textx{ 80 };
    float startbutton_texty{ 30 };
    sf::Text startbutton_text(font, "START", normaltext_size);
    startbutton_text.setOrigin({startbutton_textx/2, startbutton_texty/2});
    startbutton_text.setPosition(button_position);
    
    //start button boundaries
    float startbuttonx_lbound{ button_position.x - startbutton_bgx/2 }; //origin +- half of size
    float startbuttonx_ubound{ button_position.x + startbutton_bgx/2 };
    float startbuttony_lbound{ button_position.y - startbutton_bgy/2 };
    float startbuttony_ubound{ button_position.y + startbutton_bgy/2 };

*/

struct Bounds {
public:
    float x_ubound;
    float x_lbound;
    float y_ubound;
    float y_lbound;
};

class Button {
public:
    sf::Vector2f bg_dims;
    sf::Vector2f text_dims;
    sf::Color fill_color;
    sf::Color outline_color;
    float outline_thickness;
    sf::Vector2f pos;
    sf::Font font;
    std::string text;
    unsigned int text_size;
    Bounds bounds;

    std::vector<sf::Drawable*> drawables;
    
public:
    Button(sf::Vector2f s_bg_dims, // constructor
        sf::Vector2f s_text_dims,
        sf::Color s_fill_color,
        sf::Color s_outline_color,
        float s_outline_thickness,
        sf::Vector2f s_pos,
        sf::Font s_font,
        std::string s_text,
        unsigned int s_text_size,
        Bounds s_bounds)
        : 
        bg_dims(s_bg_dims),
        text_dims(s_text_dims),
        fill_color(s_fill_color),
        outline_color(s_outline_color),
        outline_thickness(s_outline_thickness),
        pos(s_pos),
        font(s_font),
        text(s_text),
        text_size(s_text_size),
        bounds(s_bounds)
        {
            InitBtn();
            std::cout << "Initialized!\n";
        };
    
    void InitBtn() {
        //create button
        sf::RectangleShape btn{ bg_dims };
        btn.setFillColor(fill_color);
        btn.setOutlineColor(outline_color);
        btn.setOutlineThickness(outline_thickness);
        btn.setOrigin(bg_dims / (float)2.0);
        btn.setPosition(pos);

        // create text
        sf::Text btn_text(font, text, text_size);
        btn_text.setOrigin(text_dims / (float)2.0);
        btn_text.setPosition(pos);

        drawables.push_back(&btn);
        drawables.push_back(&btn_text);
    }
};


class StartBtn : public Button {
public: 
    StartBtn() : 
        Button({150, 100}, // bg dims
                {80, 30}, // text dims
                {30, 170, 0}, // fill color (green)
                {255, 255, 255}, // outline color (black) 
                20, // outline thickness
                {300, 400}, // position
                (sf::Font)"CaviarDreams.ttf", // font
                "START", // text
                30, // text size
                {300-150/2, 300+150/2, 400-100/2, 400+100/2}){}
};


void test_button(Button);
void button_example();
void draw(sf::RenderWindow&, const std::vector<Button>&);




int main() {

    sf::RenderWindow window(sf::VideoMode({600,600}), "Snake");
    const std::optional<sf::Vector2u> windowsize_v{{600, 600}};
    window.setMinimumSize(windowsize_v);
    window.setMinimumSize(windowsize_v);

    std::vector<Button> obj_list;
    StartBtn sbtn;
    obj_list.push_back(sbtn);

    sf::RectangleShape bruh {{100, 100}};

    while(window.isOpen()) {
        //event functionality
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // main
        draw(window, obj_list);
        window.display();

    }

    /*sf::Drawable* drawables[1];
    sf::RectangleShape bruh {{100, 100}};
    drawables[0] = &bruh;*/

    /*std::vector<sf::Drawable*> drawables;
    sf::RectangleShape bruh {{100, 100}};
    drawables.push_back(&bruh);*/


    return 0;
}


void draw(sf::RenderWindow& window, const std::vector<Button>& obj_list) {
    for (int i{ 0 }; i < obj_list.size(); i++) {
        for (int j{ 0 }; j < obj_list[i].drawables.size(); j++) {
            window.draw(*(obj_list[i].drawables[j]));
        }        
    }
}

void test_button(Button btn) {
        // test bg dims
    std::cout << "bg dims " << btn.bg_dims.x << ", " << btn.bg_dims.y << "\n";
    
    // test text dims
    std::cout << "text dims " << btn.text_dims.x << ", " << btn.text_dims.y << "\n";

    // test fill color
    std::cout << "fill col " << (int)btn.fill_color.r << ", " << (int)btn.fill_color.g << ", " << (int)btn.fill_color.b << "\n";

    // test outline color
    std::cout << "outline col " << (int)btn.outline_color.r << ", " << (int)btn.outline_color.g << ", " << (int)btn.outline_color.b << "\n";

    // test outline thickness
    std::cout << "outline thick " << btn.outline_thickness << "\n";

    // test position
    std::cout << "pos " << btn.pos.x << ", " << btn.pos.y << "\n";

    // test font
    std::cout << "font " << btn.font.getInfo().family << "\n";

    // test text
    std::cout << "text " << btn.text << "\n";

    // test textsize
    std::cout << "text size " << btn.text_size << "\n";
}

void button_example() {
    Button btn = {{150, 100}, // bg dims
                {80, 30}, // text dims
                {30, 170, 0}, // fill color (green)
                {255, 255, 255}, // outline color (black) 
                {20}, // outline thickness
                {300, 400}, // position
                (sf::Font)"CaviarDreams.ttf", // font
                {"START"}, // text
                {30}, // text size
                {300-150/2, 300+150/2, 400-100/2, 400+100/2}};
    test_button(btn);
}