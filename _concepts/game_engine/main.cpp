#include <utility>
#include <iostream>
#include <variant>
#include <vector>
#include <typeinfo>

namespace game_engine {
    struct rendering {};
};

namespace game::entity::concepts {
    template <typename T>
    concept movable = requires (T value) {
        value.velocity;
        value.position;
    };

    template <typename T>
    concept renderable = requires (const T value) {
        value.render_to(std::declval<game_engine::rendering&>());
    };

    template <typename T>
    concept has_behavior = requires (T value) {
        value.behave();
    };
};

namespace game::entity::implementations {
    struct character { // renderable movable has_behavior
        void render_to(game_engine::rendering&) const {}
        void behave() {}
        const int velocity = 2;
        const std::pair<int, int> position = {0, 0};
    };

    struct tree { // renderable
        void render_to(game_engine::rendering&) const {}
        const std::pair<int, int> position = {0, 0};
    };

    struct hidden_magic_spike {  // has_behavior
        void behave() {}
    };
};

// usage
// 用于std::variant遍历的operator操作符重载
// Refer to https://www.cppstories.com/2019/02/2lines3featuresoverload.html/
template <typename ... Ts>
struct overload: Ts... {
    using Ts::operator()...;
};

// 根据 overload(Ts..) 推导出 lambda表达式类型
template <typename ... Ts>
overload(Ts...) -> overload<Ts...>;

auto main(int argc, char** argv) -> int {
    using namespace game::entity::concepts;
    using namespace game::entity::implementations;

    // entities 
    using entity_type = std::variant<character, tree, hidden_magic_spike>;
    using entity_collection = std::vector<entity_type>;

    auto entities = entity_collection {
        character{},
        tree{},
        hidden_magic_spike{}
    }; 

    // visitors: 
    const auto move_visitor = overload {
        [](movable auto arg) {
            const auto [x, y] = arg.position;
            std::cout << "-" << typeid(decltype(arg)).name() << "\n" 
                << "    with velocity=" << arg.velocity <<
                " position={" << x << "," << y << "}\n";
        },
        [](auto) {/* default case */}
    };

    const auto rendering_visitor = overload {
        [](renderable auto arg) {
            std::cout << "-" << typeid(decltype(arg)).name() << "\n";
        },
        [](auto) {/* default case */}
    };

    const auto behave_visitor = overload {
        [](has_behavior auto arg) {
            std::cout << "-" << typeid(decltype(arg)).name() << "\n";
        },
        [](auto) {/* default case */}
    };

    // usage:
    std::cout << "move: \n";
    for(auto& value: entities) {
        std::visit(move_visitor, value);
    }

    std::cout << "render: \n";
    for(auto& value: entities) {
        std::visit(rendering_visitor, value);
    }

    std::cout << "behave: \n";
    for(auto& value: entities) {
        std::visit(behave_visitor, value);
    }
    return EXIT_SUCCESS;
}