<?php
require_once 'config.php';
header('Content-Type: application/json');

session_start();

$response = ['success' => false, 'message' => ''];

try {
    $action = $_POST['action'] ?? '';
    
    switch ($action) {
        case 'add_entry':
            if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
                throw new Exception('Invalid request method');
            }
            
            $email = trim($_POST['email']);
            $title = trim($_POST['title']);
            $comment = trim($_POST['comment']);
            
            // Validation
            if (empty($email) || empty($title) || empty($comment)) {
                throw new Exception('All fields are required');
            }
            
            if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
                throw new Exception('Invalid email format');
            }
            
            if (strlen($title) > 255) {
                throw new Exception('Title is too long');
            }
            
            $stmt = $pdo->prepare("INSERT INTO entries (author_email, title, comment) VALUES (?, ?, ?)");
            $success = $stmt->execute([$email, $title, $comment]);
            
            if ($success) {
                $response = [
                    'success' => true,
                    'message' => 'Thank you for your submission!'
                ];
            } else {
                throw new Exception('Failed to save entry');
            }
            break;
            
        case 'update_entry':
            if (!isset($_SESSION['admin_logged_in'])) {
                throw new Exception('Unauthorized');
            }
            
            $id = (int)$_POST['id'];
            $title = trim($_POST['title']);
            $comment = trim($_POST['comment']);
            
            if (empty($title) || empty($comment)) {
                throw new Exception('Title and comment are required');
            }
            
            $stmt = $pdo->prepare("UPDATE entries SET title = ?, comment = ? WHERE id = ?");
            $success = $stmt->execute([$title, $comment, $id]);
            
            if ($success) {
                $response = [
                    'success' => true,
                    'message' => 'Entry updated successfully'
                ];
            } else {
                throw new Exception('Failed to update entry');
            }
            break;
            
        case 'delete_entry':
            if (!isset($_SESSION['admin_logged_in'])) {
                throw new Exception('Unauthorized');
            }
            
            $id = (int)$_POST['id'];
            
            $stmt = $pdo->prepare("DELETE FROM entries WHERE id = ?");
            $success = $stmt->execute([$id]);
            
            if ($success) {
                $response = [
                    'success' => true,
                    'message' => 'Entry deleted successfully'
                ];
            } else {
                throw new Exception('Failed to delete entry');
            }
            break;
            
        default:
            throw new Exception('Invalid action');
    }
} catch (Exception $e) {
    $response['message'] = $e->getMessage();
}

echo json_encode($response);