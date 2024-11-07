#include <iostream>
#include <string>
#include<algorithm>
using namespace std;

const int MAX_COMMENTS = 10; // Maximum comments per post

// Define a structure for User Profile in a Binary Search Tree (BST) node
struct Profile {
    int userID;
    string username;
    string email;
    string password;
    int followersCount;
    int followingCount;
    Profile* left;
    Profile* right;

    Profile(int id, string user, string mail, string pass) :
        userID(id), username(user), email(mail), password(pass),
        followersCount(0), followingCount(0), left(nullptr), right(nullptr) {}
};

// Define a structure for Posts
struct Post {
    int postID;
    int userID; // ID of the user who created the post
    string content;
    int likesCount;
    string comments[MAX_COMMENTS]; // Array for comments
    int commentCount;
};

// Root of the Profile BST
Profile* root = nullptr;

// Array for posts
Post posts[100];
int postCount = 0;

// Function to insert a profile in BST
Profile* insertProfile(Profile* root, Profile* newProfile) {
    if (!root) return newProfile;
    if (newProfile->userID < root->userID)
        root->left = insertProfile(root->left, newProfile);
    else if (newProfile->userID > root->userID)
        root->right = insertProfile(root->right, newProfile);
    return root;
}

// Function to search for a profile by userID
Profile* searchProfile(Profile* root, int userID) {
    if (!root || root->userID == userID) return root;
    if (userID < root->userID) return searchProfile(root->left, userID);
    return searchProfile(root->right, userID);
}

// Function to create a user profile
void createProfile() {
    int userID;
    string username, email, password;
    cout << "Enter a unique User ID: ";
    cin >> userID;
    cin.ignore();

    if (searchProfile(root, userID)) {
        cout << "Error: User ID already exists. Please try again." << endl;
        return;
    }

    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Password: ";
    getline(cin, password);

    Profile* newProfile = new Profile(userID, username, email, password);
    root = insertProfile(root, newProfile);
    cout << "Profile created for user: " << username << endl;
}

// Function to display profile details
void displayProfile() {
    int userID;
    cout << "Enter User ID to view profile: ";
    cin >> userID;

    Profile* profile = searchProfile(root, userID);
    if (profile) {
        cout << "User ID: " << profile->userID << endl;
        cout << "Username: " << profile->username << endl;
        cout << "Email: " << profile->email << endl;
        cout << "Followers: " << profile->followersCount << endl;
        cout << "Following: " << profile->followingCount << endl;
    } else {
        cout << "Profile not found." << endl;
    }
}

// Function to create a post
void createPost() {
    if (postCount >= 100) {
        cout << "Maximum post limit reached." << endl;
        return;
    }

    int userID, postID;
    string content;
    cout << "Enter User ID to create a post: ";
    cin >> userID;
    cin.ignore();

    if (!searchProfile(root, userID)) {
        cout << "Error: User ID not found. Please create a profile first." << endl;
        return;
    }

    cout << "Enter a unique Post ID: ";
    cin >> postID;
    cin.ignore();

    for (int i = 0; i < postCount; i++) {
        if (posts[i].postID == postID) {
            cout << "Error: Post ID already exists. Please try again." << endl;
            return;
        }
    }

    cout << "Enter Post Content: ";
    getline(cin, content);

    posts[postCount++] = { postID, userID, content, 0, {}, 0 };
    cout << "Post created by user " << userID << ": " << content << endl;
}

// Function to like a post
void likePost() {
    int postID;
    cout << "Enter Post ID to like: ";
    cin >> postID;

    for (int i = 0; i < postCount; i++) {
        if (posts[i].postID == postID) {
            posts[i].likesCount++;
            cout << "Post " << postID << " now has " << posts[i].likesCount << " likes." << endl;
            return;
        }
    }
    cout << "Post not found." << endl;
}

// Function to add a comment to a post
void addComment() {
    int postID;
    string comment;
    cout << "Enter Post ID to comment on: ";
    cin >> postID;
    cin.ignore();

    for (int i = 0; i < postCount; i++) {
        if (posts[i].postID == postID) {
            if (posts[i].commentCount < MAX_COMMENTS) {
                cout << "Enter Comment: ";
                getline(cin, comment);
                posts[i].comments[posts[i].commentCount++] = comment;
                cout << "Comment added to post " << postID << ": " << comment << endl;
            } else {
                cout << "Maximum comment limit reached for this post." << endl;
            }
            return;
        }
    }
    cout << "Post not found." << endl;
}

// Function to display all posts by a user
void displayUserPosts() {
    int userID;
    cout << "Enter User ID to view posts: ";
    cin >> userID;

    cout << "Posts by User " << userID << ":" << endl;
    bool found = false;
    for (int i = 0; i < postCount; i++) {
        if (posts[i].userID == userID) {
            found = true;
            cout << "Post ID: " << posts[i].postID << endl;
            cout << "Content: " << posts[i].content << endl;
            cout << "Likes: " << posts[i].likesCount << endl;
            cout << "Comments:" << endl;
            for (int j = 0; j < posts[i].commentCount; j++) {
                cout << "- " << posts[i].comments[j] << endl;
            }
            cout << "-----------------------------" << endl;
        }
    }
    if (!found) cout << "No posts found for this user." << endl;
}

int main() {
    int choice;
    do {
        cout << "\n----- Social Media Management System -----" << endl;
        cout << "1. Create Profile" << endl;
        cout << "2. Display Profile" << endl;
        cout << "3. Create Post" << endl;
        cout << "4. Like Post" << endl;
        cout << "5. Add Comment to Post" << endl;
        cout << "6. Display User Posts" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number from 1 to 7." << endl;
            continue;
        }

        switch (choice) {
            case 1: createProfile(); break;
            case 2: displayProfile(); break;
            case 3: createPost(); break;
            case 4: likePost(); break;
            case 5: addComment(); break;
            case 6: displayUserPosts(); break;
            case 7: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
