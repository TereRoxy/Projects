CREATE DATABASE IF NOT EXISTS guestbook;
USE guestbook;

drop TABLE IF EXISTS entries;
drop TABLE IF EXISTS admins;

CREATE TABLE IF NOT EXISTS entries (
    id INT AUTO_INCREMENT PRIMARY KEY,
    author_email VARCHAR(255) NOT NULL,
    title VARCHAR(255) NOT NULL,
    comment TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS admins (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password_hash VARCHAR(255) NOT NULL
);

-- Insert a default admin (password: admin123)
INSERT INTO admins (username, password_hash) VALUES ('admin', '$2y$10$92IXUNpkjO0rOQ5byMi.Ye4oKoEa3Ro9llC/.og/at2.uheWG/igi');

Insert into entries (author_email, title, comment) VALUES
('example@gmail.com', 'First Entry', 'This is the first comment!');

select * from entries;