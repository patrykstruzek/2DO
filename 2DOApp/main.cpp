#include <2DOApp/app.hpp>

using namespace twodo;

int main()
{
    App app{};

    app.run();
    
    // App app{};

    // auto result = app.run();
    // if(!result)
    // {
    //     return EXIT_FAILURE;
    // }

    // auto db_path =  String("../../test/db");
    // std::shared_ptr<UserDb> udb = std::make_shared<UserDb>(db_path);
    // std::shared_ptr<MockUserInputHandler> ih = std::make_shared<MockUserInputHandler>();
    // std::shared_ptr<MockDisplayer> d = std::make_shared<MockDisplayer>();

    // if (!udb || !ih || !d)
    // {
    //     std::cerr << "Failed to initialize one or more objects." << std::endl;
    //     return EXIT_FAILURE;
    // }

    // std::cout << "Register:\n";
    // auto rm = std::make_unique<RegisterManager>(udb, ih, d);
    // auto result = rm->singup();
    // if (!result)
    // {
    //     std::cerr << "Something goes wrong!";
    // }

    // rm.reset();
    // udb.reset();
    // ih.reset();
    // d.reset();

    // std::shared_ptr<UserDb> udb2 = std::make_shared<UserDb>(db_path);
    // std::shared_ptr<MockUserInputHandler> ih2 = std::make_shared<MockUserInputHandler>();
    // std::shared_ptr<MockDisplayer> d2 = std::make_shared<MockDisplayer>();

    // std::cout << "Login:\n";
    // auto am = std::make_unique<AuthManager>(udb2, ih2, d2);
    // auto user = am->login();
    // if (!user)
    // {
    //     std::cerr << "Something goes wrong!";
    // }

    // am.reset();
    // udb2.reset();
    // ih2.reset();
    // d2.reset();
    // fs::remove(db_path + ".db3");
}