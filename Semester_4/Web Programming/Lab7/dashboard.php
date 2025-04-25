<?php
session_start();
require_once 'config.php';

// Check if user is logged in
if (!isset($_SESSION['admin_logged_in'])) {
    header('Location: admin.php');
    exit;
}

// Logout functionality
if (isset($_GET['logout'])) {
    session_destroy();
    header('Location: index.php');
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Dashboard</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <?php include 'navigation.php'; ?>
    <div class="container">
        <h1>Admin Dashboard</h1>
        <p>Welcome, <?php echo htmlspecialchars($_SESSION['admin_username']); ?>!</p>
        
        <div class="admin-actions">
            <a href="?logout" class="admin-link">Logout</a>
        </div>
        
        <div class="entries-controls">
            <h2>Manage Entries</h2>
            <div class="filter-controls">
                <label for="filterAuthor">Filter by Author:</label>
                <input type="text" id="filterAuthor" placeholder="Enter email">
                
                <label for="filterTitle">Filter by Title:</label>
                <input type="text" id="filterTitle" placeholder="Enter title">
                
                <button id="applyFilter">Apply Filter</button>
                <button id="resetFilter">Reset</button>
            </div>
        </div>
        
        <div id="adminEntriesContainer"></div>
        <div class="pagination">
            <button id="adminPrevPage" disabled>Previous</button>
            <span id="adminPageInfo">Page 1</span>
            <button id="adminNextPage">Next</button>
        </div>
    </div>

    <script src="js/script.js"></script>
</body>
</html>