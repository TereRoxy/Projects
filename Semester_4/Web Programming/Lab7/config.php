<?php
// Database configuration
define('DB_HOST', 'localhost');      // or '127.0.0.1' if localhost doesn't work
define('DB_NAME', 'guestbook');      // your database name
define('DB_USER', 'root');           // your MySQL username
define('DB_PASS', '');   // your MySQL password (leave empty if no password)
define('DB_PORT', '3306');           // default MySQL port

// Error reporting
error_reporting(E_ALL);
ini_set('display_errors', 1);

// Create PDO instance
try {
    $dsn = "mysql:host=".DB_HOST.";port=".DB_PORT.";dbname=".DB_NAME.";charset=utf8mb4";
    
    $pdo = new PDO($dsn, DB_USER, DB_PASS, [
        PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
        PDO::ATTR_EMULATE_PREPARES => false, // Important for security
    ]);
    
    // Test connection
    $pdo->query("SELECT 1");
} catch (PDOException $e) {
    die("Database connection failed: " . $e->getMessage());
}

// Helper function to sanitize input
function sanitizeInput($data) {
    return htmlspecialchars(trim($data), ENT_QUOTES, 'UTF-8');
}