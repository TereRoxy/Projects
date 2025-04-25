<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>All Guest Book Entries</title>
    <link rel="stylesheet" href="style.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
</head>
<body>
    <?php include 'navigation.php'; ?>
    <div class="container">
        <div class="guest-entries">
            <h2>All Entries</h2>
            <div id="entriesContainer"></div>
            <div class="pagination">
                <button id="prevPage" disabled>Previous</button>
                <span id="pageInfo">Page 1</span>
                <button id="nextPage">Next</button>
            </div>
        </div>
    </div>
    <script src="js/all_entries.js"></script>
</body>
</html>