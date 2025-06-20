# 🎮 Advanced Tic Tac Toe

> A modern C++/Qt-powered take on the classic game — smarter, cleaner, and packed with features.

---

## 📦 Features

🧠 **AI Difficulty Levels** (Easy, Medium, Hard)  
🔐 **User Authentication** (SHA-256 hashed)  
📈 **Stats & Replays** — Browse and replay past matches  
💾 **Persistent Storage** using **SQLite**  
🎨 **Qt-based Cross-platform GUI**  
🧪 **Unit Tested** with GoogleTest  
📦 **One-click Installer** (available in Releases)

---

## 🧱 Architecture

```txt
[Qt GUI] ⇄ [Wrapper API] ⇄ [Game Logic] + [AI Engine] + [UserSystem(SQLite)]
