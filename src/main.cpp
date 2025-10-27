#include <firebase/app.h>
#include <firebase/auth.h>
#include <firebase/future.h>
#include <firebase/firestore.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

void assert(bool condition, const string &message)
{
    if (!condition)
        throw runtime_error(message);
}

void await(const firebase::FutureBase &future)
{
    while (future.status() == firebase::kFutureStatusPending)
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << ".";
        cout.flush();
    }
    cout << endl;
}

int main()
{
    cout << "Firebase C++ SDK desktop" << endl;
    cout << "MRE for crash on Windows" << endl;
    cout << "===============================" << endl;

    try
    {
        // Initialize Firebase App
        cout << "\nInitializing Firebase..." << endl;

        firebase::App *app = nullptr;

        // Read configuration from file
        const string config_path = "google-services-desktop.json";
        ifstream config_file(config_path);
        assert(config_file.is_open(), "Failed to open configuration file: " + config_path);
        string config_content((istreambuf_iterator<char>(config_file)), istreambuf_iterator<char>());
        firebase::AppOptions options;
        options.LoadFromJsonConfig(config_content.c_str());

        // Create the Firebase App
        app = firebase::App::Create(options);
        assert(app != nullptr, "Failed to create Firebase app!");
        cout << "Firebase app created successfully!" << endl;

        // Read credentials from file
        const string credentials_path = "credentials.txt";
        ifstream credentials_file(credentials_path);
        assert(credentials_file.is_open(), "Failed to open credentials file: " + credentials_path);
        string email, password;
        getline(credentials_file, email);
        getline(credentials_file, password);
        credentials_file.close();
        assert(!email.empty() && !password.empty(), "Credentials file is empty or invalid!");
        cout << "\nAttempting to sign in with:" << endl;
        cout << "Email: " << email << endl;
        cout << "Password: " << password << endl;

        // Sign in with email and password
        firebase::auth::Auth *auth = firebase::auth::Auth::GetAuth(app);
        assert(auth != nullptr, "Failed to initialize Firebase Auth!");
        firebase::Future<firebase::auth::AuthResult> sign_in_future =
            auth->SignInWithEmailAndPassword(email.c_str(), password.c_str());
        cout << "Signing in..." << endl;
        await(sign_in_future);
        cout << endl;

        assert(sign_in_future.status() == firebase::kFutureStatusComplete, "Sign-in operation did not complete successfully. Status: " + to_string(sign_in_future.status()));
        assert(sign_in_future.error() == firebase::auth::kAuthErrorNone, "Sign-in operation failed with error: " + string(sign_in_future.error_message()));
        firebase::auth::AuthResult result = *sign_in_future.result();
        firebase::auth::User user = result.user;
        cout << "\nSuccessfully signed in!" << endl;
        cout << "User ID: " << user.uid() << endl;
        cout << "Email: " << user.email() << endl;

        cout << "\nPress Enter to retrieve document...";
        cin.get();

        // Retrieve document from Firestore
        firebase::firestore::Firestore *firestore = firebase::firestore::Firestore::GetInstance(app);
        assert(firestore != nullptr, "Failed to initialize Firestore!");
        firebase::firestore::DocumentReference doc_ref = firestore->Collection("User").Document(user.uid());
        cout << "Retrieving document for user ID: " << user.uid() << endl;
        firebase::Future<firebase::firestore::DocumentSnapshot> get_future = doc_ref.Get();
        await(get_future);
        assert(get_future.status() == firebase::kFutureStatusComplete, "Document retrieval did not complete successfully. Status: " + to_string(get_future.status()));
        assert(get_future.error() == firebase::firestore::kErrorNone, "Document retrieval failed with error: " + string(get_future.error_message()));
        firebase::firestore::DocumentSnapshot doc_snapshot = *get_future.result();
        assert(doc_snapshot.exists(), "Document does not exist!");

        cout << "\nDocument retrieved successfully!" << endl;
        cout << "User ID: " << doc_snapshot.id() << endl;
        cout << "Email: " << doc_snapshot.Get("email").string_value() << endl;

        // Clean up
        cout << "Cleaning up." << endl;
        delete firestore;
        delete auth;
        delete app;

        cout << "\nPress Enter to exit...";
        cin.get();

        return 0;
    }
    catch (const exception &e)
    {
        cerr << "ERROR: " << e.what() << endl;
        cout << "\nPress Enter to exit...";
        cin.get();
        return EXIT_FAILURE;
    }
}
