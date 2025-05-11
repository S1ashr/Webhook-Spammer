// made by S1ashr
// https://github.com/S1ashr


#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) 
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool send_to_discord(const string& webhook_url, const string& message) 
{
    CURL* curl = curl_easy_init();
    if (!curl) return false;
    string readBuffer;
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json"); 
    string escaped_msg;

    for (char c : message) {
        if (c == '"') escaped_msg += "\\\"";
        else if (c == '\\') escaped_msg += "\\\\";
        else escaped_msg += c;
    }

    string json_payload = "{\"content\":\"" + escaped_msg + "\"}";
    curl_easy_setopt(curl, CURLOPT_URL, webhook_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return (res == CURLE_OK);
}

int main() 
{
    string webhook_url, message;
    SetConsoleTitleA("Webhook Spammer by S1ashr");
    cout << "Webhook Spammer by S1ashr\n";
    cout << "\n";
    cout << "Github: https://github.com/S1ashr\n";
    cout << "Discord: s1ashr__\n";
    cout << "Latest Commit 2025-05-10\n";
    cout << "\n";
    cout << "if you were sold this you got scammed(and why are you buying webhook spammers?)\n";
    cout << "\n";
    cout << "Enter URL: ";
    getline(cin, webhook_url);
    cout << "Enter message to send: ";
    getline(cin, message);

    while (true)
    {
        if (send_to_discord(webhook_url, message)) {
            cout << "Message sent successfully!\n";
        }
        else {
            cerr << "Failed to send message.\n";
        }
    }
    return 0;
}