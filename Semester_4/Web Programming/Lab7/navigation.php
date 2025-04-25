<?php
$current_page = basename($_SERVER['PHP_SELF']);
?>
<nav class="nav-menu">
    <ul>
        <li><a href="index.php" <?php echo $current_page == 'index.php' ? 'class="active"' : ''; ?>>Home</a></li>
        <li><a href="all_entries.php" <?php echo $current_page == 'all_entries.php' ? 'class="active"' : ''; ?>>View All Entries</a></li>
        <li><a href="admin.php" <?php echo $current_page == 'admin.php' ? 'class="active"' : ''; ?>>Admin Login</a></li>
        <li><a href="about.php" <?php echo $current_page == 'about.php' ? 'class="active"' : ''; ?>>About</a></li>
    </ul>
</nav>