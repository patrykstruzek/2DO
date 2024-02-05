#pragma once

#include <functional>
#include <memory>

#include <2DOCore/user.hpp>
#include <Utils/result.hpp>
#include <Utils/type.hpp>
#include <Utils/util.hpp>

namespace tdu = twodoutils;
namespace tdc = twodocore;

namespace twodo {
class [[nodiscard]] Page : std::enable_shared_from_this<Page> {
  public:
    Page(const Page&) = default;
    Page& operator=(const Page&) = default;
    Page(Page&&) = default;
    Page& operator=(Page&&) = default;

    Page(std::function<void()> content, bool is_menu_event = true)
        : m_content{std::move(content)}, m_menu_event{is_menu_event} {}

    void execute() { m_content(); }

    void attach(const String& option, std::shared_ptr<Page> child) {
        m_childs.insert({option, child});
        child->m_parent = shared_from_this();
    }

    bool is_menu_event() const { return m_menu_event; }

    std::shared_ptr<Page> get_page(const String& option) const {
        auto it = m_childs.find(option);
        if (it != m_childs.end()) {
            return it->second;
        }
        return nullptr;
    }

  private:
    std::function<void()> m_content;
    HashMap<String, std::shared_ptr<Page>> m_childs;
    std::shared_ptr<Page> m_parent{};
    bool m_menu_event;

    friend class Menu;
};

class [[nodiscard]] Menu {
  public:
    Menu(Menu&&) = default;
    Menu& operator=(Menu&&) = default;
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

    Menu(std::shared_ptr<Page> initial_page,
         std::shared_ptr<tdu::IPrinter> iprinter,
         std::shared_ptr<tdu::IUserInputHandler> input_handler_)
        : current_page{std::move(initial_page)},
          printer{iprinter},
          input_handler{input_handler_} {}

    void run(const String& quit_input = String{}) {
        while (true) {
            execute_current_page();

            String user_choice = get_user_choice();
            if (handle_quit(user_choice, quit_input)) {
                break;
            }

            navigate_or_display_error(user_choice, quit_input);

            tdu::clear_term();
        }
    }

  private:
    std::shared_ptr<Page> current_page;
    std::shared_ptr<tdu::IPrinter> printer;
    std::shared_ptr<tdu::IUserInputHandler> input_handler;

    String get_user_choice() const { return input_handler->get_input(); }

    void execute_current_page() {
        if (current_page) {
            current_page->execute();
        }
    }

    bool handle_quit(const String& user_choice, const String& quit_input) {
        if (user_choice == quit_input) {
            return navigate_to_parent_or_exit();
        }
        return false;
    }

    bool navigate_to_parent_or_exit() {
        const auto parent_page = current_page;
        if (!parent_page) {
            return true;
        }
        current_page = parent_page;
        return false;
    }

    void navigate_or_display_error(const String& user_choice,
                                   const String& quit_input) {
        std::shared_ptr<Page> selected_page =
            current_page->get_page(user_choice);
        if (!selected_page && user_choice != quit_input) {
            display_invalid_option_error();
        } else {
            perform_page_navigation_or_execution(selected_page);
        }
    }

    void display_invalid_option_error() const {
        printer->msg_print("Invalid option!\n");
        tdu::sleep(2000);
    }

    void perform_page_navigation_or_execution(
        std::shared_ptr<Page> selected_page) {
        if (selected_page && !selected_page->is_menu_event()) {
            selected_page->execute();
        } else if (selected_page) {
            current_page = selected_page;
        }
    }
};

// enum class AuthErr {
//     InvalidNameLength = 1,
//     AlreadyExistingName,
//     InvalidPassLength,
//     MissingUpperCase,
//     MissingLowerCase,
//     MissingNumber,
//     MissingSpecialCharacter,
//     UserNotFound,
//     AllTriesExhausted,
//     DbErr,
// };

// class [[nodiscard]] AuthenticationManager {
//   public:
//     AuthenticationManager(AuthenticationManager&& other) = default;
//     AuthenticationManager& operator=(AuthenticationManager&& other) =
//     default; AuthenticationManager(const AuthenticationManager&) = delete;
//     AuthenticationManager& operator=(const AuthenticationManager&) = delete;

//     AuthenticationManager(std::shared_ptr<tdc::UserDb> user_db)
//         : m_user_db{user_db} {}

//     tdu::Result<void, AuthErr> username_validation(StringView username);
//     tdu::Result<void, AuthErr> password_validation(StringView password);

//   private:
//     std::shared_ptr<tdc::UserDb> m_user_db;

//     bool is_in_db(const tdc::User& user);
// };

// class [[nodiscard]] RegisterManager {
//   public:
//     RegisterManager(RegisterManager&& other) = default;
//     RegisterManager& operator=(RegisterManager&& other) = default;
//     RegisterManager(const RegisterManager&) = delete;
//     RegisterManager& operator=(const RegisterManager&) = delete;

//     RegisterManager(std::shared_ptr<tdc::UserDb> udb,
//                     std::shared_ptr<tdu::IUserInputHandler<String>> ihandler,
//                     std::shared_ptr<tdu::IPrinter> iprinter)
//         : m_udb{udb}, m_ihandler{ihandler}, m_printer{iprinter} {}

//     [[nodiscard]] tdu::Result<tdc::User, AuthErr> singup();

//     [[nodiscard]] tdu::Result<void, AuthErr> username_validation(
//         StringView username) const;

//     [[nodiscard]] tdu::Result<void, AuthErr> password_validation(
//         const String& password) const;

//   private:
//     std::shared_ptr<tdc::UserDb> m_udb;
//     std::shared_ptr<tdu::IUserInputHandler<String>> m_ihandler;
//     std::shared_ptr<tdu::IPrinter> m_printer;
// };

// class [[nodiscard]] AuthManager {
//   public:
//     AuthManager(AuthManager&& other) = default;
//     AuthManager& operator=(AuthManager&& other) = default;
//     AuthManager(const AuthManager&) = delete;
//     AuthManager& operator=(const AuthManager&) = delete;

//     AuthManager(std::shared_ptr<tdc::UserDb> udb,
//                 std::shared_ptr<tdu::IUserInputHandler<String>> ihandler,
//                 std::shared_ptr<tdu::IPrinter> iprinter)
//         : m_udb{udb}, m_ihandler{ihandler}, m_printer{iprinter} {}

//     [[nodiscard]] tdu::Result<tdc::User, AuthErr> login();

//     [[nodiscard]] tdu::Result<void, AuthErr> auth_username();

//     [[nodiscard]] tdu::Result<tdc::User, AuthErr> auth_password(
//         const String& username);

//   private:
//     std::shared_ptr<tdc::UserDb> m_udb;
//     std::shared_ptr<tdu::IUserInputHandler<String>> m_ihandler;
//     std::shared_ptr<tdu::IPrinter> m_printer;
// };
}  // namespace twodo