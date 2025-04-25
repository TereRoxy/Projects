<?php
session_start();
require_once 'config.php';

// Check if user is already logged in as admin
if (isset($_SESSION['admin_logged_in']) && $_SESSION['admin_logged_in'] === true) {
    header('Location: dashboard.php');
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Guest Book</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <?php include 'navigation.php'; ?>
    <div class="container">
        <h1>Guest Book</h1>
        
        <div class="guest-form">
            <h2>Leave a Message</h2>
            <form id="guestForm">
                <div class="form-group">
                    <label for="email">Email:</label>
                    <input type="email" id="email" name="email" required>
                    <span class="error" id="emailError"></span>
                </div>
                
                <div class="form-group">
                    <label for="title">Title:</label>
                    <input type="text" id="title" name="title" required maxlength="255">
                    <span class="error" id="titleError"></span>
                </div>
                
                <div class="form-group">
                    <label for="comment">Comment:</label>
                    <textarea id="comment" name="comment" required></textarea>
                    <span class="error" id="commentError"></span>
                </div>
                
                <button type="submit">Submit</button>
            </form>
            <div id="formMessage"></div>
        </div>
    </div>

    <script src="js/script.js"></script>
</body>
</html>