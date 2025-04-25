<?php
require_once 'config.php';
header('Content-Type: application/json');

$perPage = isset($_GET['perPage']) ? (int)$_GET['perPage'] : 4; // Default to 4 if not specified

try {
    // Get pagination parameters
    $page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
    $perPage = 4;
    $offset = ($page - 1) * $perPage;
    
    // Get filter parameters
    $authorFilter = isset($_GET['author']) ? trim($_GET['author']) : '';
    $titleFilter = isset($_GET['title']) ? trim($_GET['title']) : '';
    $isAdmin = isset($_GET['admin']) && $_GET['admin'] === 'true';
    
    // Base query
    $query = "SELECT * FROM entries WHERE 1=1";
    $params = [];
    $types = [];
    
    // Add author filter if provided
    if (!empty($authorFilter)) {
        $query .= " AND author_email LIKE ?";
        $params[] = "%$authorFilter%";
        $types[] = PDO::PARAM_STR;
    }
    
    // Add title filter if provided
    if (!empty($titleFilter)) {
        $query .= " AND title LIKE ?";
        $params[] = "%$titleFilter%";
        $types[] = PDO::PARAM_STR;
    }
    
    // Get total count for pagination (without LIMIT/OFFSET)
    $countQuery = str_replace('SELECT *', 'SELECT COUNT(*) as total', $query);
    $stmt = $pdo->prepare($countQuery);
    
    // Bind parameters for count query
    foreach ($params as $i => $param) {
        $stmt->bindValue($i + 1, $param, $types[$i]);
    }
    
    $stmt->execute();
    $total = (int)$stmt->fetchColumn();
    
    // Add sorting and pagination
    $query .= " LIMIT ? OFFSET ?";
    $params[] = $perPage;
    $types[] = PDO::PARAM_INT;
    $params[] = $offset;
    $types[] = PDO::PARAM_INT;
    
    // Execute the main query
    $stmt = $pdo->prepare($query);
    
    // Bind all parameters with their types
    foreach ($params as $i => $param) {
        $stmt->bindValue($i + 1, $param, $types[$i]);
    }
    
    $stmt->execute();
    $entries = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
    echo json_encode([
        'success' => true,
        'entries' => $entries,
        'total' => $total,
        'page' => $page,
        'perPage' => $perPage,
        'totalPages' => ceil($total / $perPage)
    ]);
} catch (PDOException $e) {
    echo json_encode([
        'success' => false,
        'message' => 'Database error: ' . $e->getMessage()
    ]);
}