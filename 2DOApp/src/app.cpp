#include "2DOApp/app.hpp"

#include <fmt/core.h>

#include <2DOCore/task.hpp>
#include <2DOCore/utils.hpp>
#include <chrono>
#include <thread>

namespace twodo
{
void App::run()
{
    tdc::create_simple_app_env("2DO", {"users.db3", "tasks.db3"});
    load_menu().run("0");
}

Menu<String> App::load_menu()
{
    std::shared_ptr<Page<String>> main = std::make_shared<Page<String>>(
        []()
        {
            fmt::print(
                "Main Menu:\n"
                "[1] Tasks\n"
                "[2] Setting\n"
                "[0] Exit\n"
                "-> ");
        });

    UserInput ui {};
    MsgDisplayer md {};
    Menu menu {main, md, ui};

    main->add_child("1", tasks_menu());
    main->add_child("2", settings_menu());

    return menu;
}

std::shared_ptr<Page<String>> App::tasks_menu()
{
    std::shared_ptr<Page<String>> tasks = std::make_shared<Page<String>>(
        []()
        {
            fmt::print(
                "Tasks:\n"
                "[1] Your tasks\n"
                "[2] Delegated tasks\n"
                "[3] Create task\n"
                "[0] Back\n"
                "-> ");
        });

    std::shared_ptr<Page<String>> your_tasks =
        std::make_shared<Page<String>>([]() { fmt::print("Your tasks:\n"); });

    std::shared_ptr<Page<String>> delegated_tasks = std::make_shared<Page<String>>(
        []()
        {
            fmt::print(
                "Tasks:\n"
                "[1] Your tasks\n"
                "[2] Delegated tasks\n"
                "[3] Create task\n"
                "[0] Back\n"
                "-> ");
        });

    std::shared_ptr<Page<String>> create_task = std::make_shared<Page<String>>(
        []()
        {
            fmt::print(
                "Tasks:\n"
                "[1] Your tasks\n"
                "[2] Delegated tasks\n"
                "[3] Create task\n"
                "[0] Back\n"
                "-> ");
        });

    return tasks;
}

std::shared_ptr<Page<String>> App::settings_menu()
{
    std::shared_ptr<Page<String>> settings = std::make_shared<Page<String>>(
        []()
        {
            fmt::print(
                "Settings:\n"
                "[1] Manage users\n"
                "[2] Advanced\n"
                "[0] Back\n"
                "-> ");
        });

    return settings;
}
}  // namespace twodo

// namespace twodo
// {
// tdc::Result<tdc::None, RunError> App::run()
// {
//     while (m_is_running)
//     {
//         tdc::clear_term();

//         std::cout << "Main Menu:\n"
//                   << "[1] Tasks\n"
//                   << "[2] Users\n"
//                   << "[3] Settings\n"
//                   << "[0] Exit\n"
//                   << "->";

//         auto main_option = get_valid_option();

//         if (main_option)
//         {
//             switch (main_option.value())
//             {
//                 case 0:
//                 {
//                     m_is_running = false;
//                     break;
//                 }
//                 case 1:
//                 {
//                     bool m_in_task_menu = true;
//                     while (m_in_task_menu)
//                     {
//                         tdc::clear_term();

//                         std::cout << "Task Menu:\n"
//                                   << "[1] Task List\n"
//                                   << "[2] Add new task\n"
//                                   << "[3] Delete task\n"
//                                   << "[4] Modify task\n"
//                                   << "[5] Add comments\n"
//                                   << "[0] Back\n"
//                                   << "->";

//                         auto task_option = get_valid_option();

//                         if (task_option)
//                         {
//                             switch (task_option.value())
//                             {
//                                 case 0:
//                                     m_in_task_menu = false;
//                                     break;
//                                 case 1:
//                                     break;
//                                 case 2:
//                                     break;
//                                 case 3:
//                                     break;
//                                 case 4:
//                                     break;
//                                 case 5:
//                                     break;
//                                 default:
//                                     std::cerr << "Invalid option. Try again!\n";
//                                     tdc::sleep(2000);
//                                     break;
//                             }
//                         }
//                         else
//                         {
//                             std::cerr << "Invalid input. Try again!\n";
//                             tdc::sleep(2000);
//                         }
//                     }
//                     break;
//                 }
//                 case 2:
//                 {
//                     std::cout << "users";
//                     break;
//                 }
//                 case 3:
//                 {
//                     std::cout << "settings";
//                     break;
//                 }
//                 default:
//                 {
//                     std::cerr << "Invalid option. Try again!\n";
//                     tdc::sleep(2000);
//                     break;
//                 }
//             }
//         }
//         else
//         {
//             std::cerr << "Invalid input. Try again!\n";
//             tdc::sleep(2000);
//         }
//     }
//     return tdc::Ok<tdc::None, RunError>({});
// }

// tdc::Result<int, InputError> App::get_valid_option() noexcept
// {
//     int value = 0;
//     std::cin >> value;
//     if (std::cin.fail())
//     {
//         std::cin.clear();
//         std::cin.ignore(INT_MAX, '\n');

//         return tdc::Err<int, InputError>(InputError::InvalidInput);
//     }
//     std::cin.ignore(INT_MAX, '\n');
//     return tdc::Ok<int, InputError>(std::move(value));
// }
// }  // namespace twodo