<?php
require_once 'config.php';

try {
    $stmt = $pdo->query("SELECT version()");
    $version = $stmt->fetchColumn();
    echo "Connected successfully. Database version: " . $version;
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}