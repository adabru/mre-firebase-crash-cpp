#include <firebase/app.h>
#include <firebase/auth.h>
#include <firebase/future.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    cout << "Firebase C++ SDK desktop" << endl;
    cout << "MRE for crash on Windows" << endl;
    cout << "===============================" << endl;

    // Initialize Firebase App
    cout << "\nInitializing Firebase..." << endl;

    firebase::App *app = nullptr;

    // Read configuration from google-services-desktop.json
    firebase::AppOptions options;
    options.set_api_key("xxx");
    options.set_app_id("xxx");
    options.set_project_id("xxx");

    app = firebase::App::Create(options);

    if (app == nullptr)
    {
        cout << "Failed to create Firebase app!" << endl;
        return -1;
    }

    cout << "Firebase app created successfully!" << endl;

    // Initialize Firebase Auth
    cout << "Initializing Firebase Auth..." << endl;
    firebase::auth::Auth *auth = firebase::auth::Auth::GetAuth(app);

    if (auth == nullptr)
    {
        cout << "Failed to initialize Firebase Auth!" << endl;
        delete app;
        return -1;
    }

    cout << "Firebase Auth initialized successfully!" << endl;

    // Sign in with email and password
    const string email = "test01@example.com";
    const string password = "Test";

    cout << "\nAttempting to sign in with:" << endl;
    cout << "Email: " << email << endl;
    cout << "Password: " << password << endl;

    firebase::Future<firebase::auth::AuthResult> sign_in_future =
        auth->SignInWithEmailAndPassword(email.c_str(), password.c_str());

    cout << "Signing in..." << endl;

    // Wait for the authentication to complete
    while (sign_in_future.status() == firebase::kFutureStatusPending)
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << ".";
        cout.flush();
    }
    cout << endl;

    if (sign_in_future.status() == firebase::kFutureStatusComplete)
    {
        if (sign_in_future.error() == firebase::auth::kAuthErrorNone)
        {
            firebase::auth::AuthResult result = *sign_in_future.result();
            firebase::auth::User user = result.user;

            cout << "\n✅ Successfully signed in!" << endl;
            cout << "User ID: " << user.uid() << endl;
            cout << "Email: " << user.email() << endl;
            cout << "Display Name: " << (user.display_name().empty() ? "Not set" : user.display_name()) << endl;
            cout << "Email Verified: " << (user.is_email_verified() ? "Yes" : "No") << endl;
        }
        else
        {
            cout << "\n❌ Authentication failed!" << endl;
            cout << "Error: " << sign_in_future.error_message() << endl;
        }
    }
    else
    {
        cout << "\n❌ Authentication operation failed!" << endl;
        cout << "Status: " << sign_in_future.status() << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.get();

    // Clean up
    cout << "Cleaning up..." << endl;
    delete app;

    return 0;
}
