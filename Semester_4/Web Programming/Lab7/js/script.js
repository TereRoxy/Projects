// script.js
$(document).ready(function() {
    // Pagination variables
    let currentPage = 1;
    let adminCurrentPage = 1;
    
    // Initialize the appropriate page
    if ($('#guestForm').length) initGuestBook();
    if ($('#adminEntriesContainer').length) initAdminDashboard();

    function initGuestBook() {
        // Load initial entries
        loadEntries(currentPage);
        
        // Form submission
        $('#guestForm').submit(function(e) {
            e.preventDefault();
            
            // Clear previous messages
            $('.error').text('');
            $('#formMessage').removeClass('error success').text('');
            
            // Validate form
            let isValid = true;
            const email = $('#email').val().trim();
            const title = $('#title').val().trim();
            const comment = $('#comment').val().trim();
            
            if (!email) {
                $('#emailError').text('Email is required');
                isValid = false;
            } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
                $('#emailError').text('Invalid email format');
                isValid = false;
            }
            
            if (!title) {
                $('#titleError').text('Title is required');
                isValid = false;
            }
            
            if (!comment) {
                $('#commentError').text('Comment is required');
                isValid = false;
            }
            
            if (!isValid) return;
            
            // Submit via AJAX
            $.ajax({
                url: 'entries.php',
                method: 'POST',
                data: {
                    action: 'add_entry',
                    email: email,
                    title: title,
                    comment: comment
                },
                dataType: 'json',
                success: function(data) {
                    if (data.success) {
                        $('#formMessage').addClass('success').text(data.message);
                        $('#guestForm')[0].reset();
                        loadEntries(currentPage);
                    } else {
                        $('#formMessage').addClass('error').text(data.message);
                    }
                },
                error: function(xhr) {
                    $('#formMessage').addClass('error').text('Failed to submit entry: ' + xhr.statusText);
                }
            });
        });
    }

    function initAdminDashboard() {
        // Load initial entries
        loadAdminEntries(adminCurrentPage);
        
        // Pagination controls
        $('#adminPrevPage').click(function() {
            if (adminCurrentPage > 1) {
                adminCurrentPage--;
                loadAdminEntries(adminCurrentPage);
            }
        });
        
        $('#adminNextPage').click(function() {
            if (adminCurrentPage < state.totalPages) {
                adminCurrentPage++;
                loadAdminEntries(adminCurrentPage);
            }
        });
        
        // Filter controls
        $('#applyFilter').click(function() {
            adminCurrentPage = 1;
            loadAdminEntries(adminCurrentPage);
        });
        
        $('#resetFilter').click(function() {
            $('#filterAuthor, #filterTitle').val('');
            adminCurrentPage = 1;
            loadAdminEntries(adminCurrentPage);
        });
    }

    function loadAdminEntries(page) {
        $('#adminEntriesContainer').html('<p>Loading entries...</p>');
        
        $.ajax({
            url: 'entries.php',
            method: 'GET',
            dataType: 'json',
            data: {
                action: 'get_entries',
                page: page,
                admin: true,
                author: $('#filterAuthor').val(),
                title: $('#filterTitle').val()
            },
            success: function(data) {
                if (data.success) {
                    renderEntries(data.entries, $('#adminEntriesContainer'), true);
                    updatePagination(data, adminCurrentPage, 'adminPageInfo', 'adminPrevPage', 'adminNextPage');
                } else {
                    $('#adminEntriesContainer').html(`<p class="error">${data.message}</p>`);
                }
            },
            error: function(xhr) {
                $('#adminEntriesContainer').html(`<p class="error">Failed to load entries: ${xhr.statusText}</p>`);
            }
        });
    }

    function renderEntries(entries, container, isAdmin) {
        if (entries.length === 0) {
            container.html('<p>No entries found.</p>');
            return;
        }
        
        let html = '';
        $.each(entries, function(index, entry) {
            html += `
                <div class="entry" data-id="${entry.id}">
                    <h3 class="entry-title">${escapeHtml(entry.title)}</h3>
                    <div class="entry-meta">
                        <span class="entry-author">${escapeHtml(entry.author_email)}</span>
                    </div>
                    <div class="entry-comment">${escapeHtml(entry.comment)}</div>
                    ${isAdmin ? renderAdminControls(entry) : ''}
                </div>
            `;
        });
        
        container.html(html);
        
        if (isAdmin) {
            container.find('.delete-btn').click(function() {
                const entryId = $(this).closest('.entry').data('id');
                if (confirm('Are you sure you want to delete this entry?')) {
                    deleteEntry(entryId);
                }
            });
            
            container.find('.edit-btn').click(function() {
                const entryId = $(this).closest('.entry').data('id');
                const entry = entries.find(e => e.id == entryId);
                showEditModal(entry);
            });
        }
    }

    function renderAdminControls(entry) {
        return `
            <div class="admin-controls">
                <button class="edit-btn">Edit</button>
                <button class="delete-btn">Delete</button>
            </div>
        `;
    }

    function updatePagination(data, currentPage, pageInfoId, prevBtnId, nextBtnId) {
        $(`#${pageInfoId}`).text(`Page ${data.page} of ${data.totalPages}`);
        $(`#${prevBtnId}`).prop('disabled', data.page <= 1);
        $(`#${nextBtnId}`).prop('disabled', data.page >= data.totalPages);
    }

    function deleteEntry(entryId) {
        $.ajax({
            url: 'entries.php',
            method: 'POST',
            data: {
                action: 'delete_entry',
                id: entryId
            },
            dataType: 'json',
            success: function(data) {
                if (data.success) {
                    loadAdminEntries(adminCurrentPage);
                } else {
                    alert(data.message);
                }
            },
            error: function(xhr) {
                alert('Failed to delete entry: ' + xhr.statusText);
            }
        });
    }

    function showEditModal(entry) {
        const modal = $(`
            <div class="modal">
                <div class="modal-content">
                    <h3>Edit Entry</h3>
                    <form id="editForm">
                        <input type="hidden" name="id" value="${entry.id}">
                        <div class="form-group">
                            <label for="editTitle">Title:</label>
                            <input type="text" id="editTitle" name="title" value="${escapeHtml(entry.title)}" required>
                        </div>
                        <div class="form-group">
                            <label for="editComment">Comment:</label>
                            <textarea id="editComment" name="comment" required>${escapeHtml(entry.comment)}</textarea>
                        </div>
                        <div class="modal-actions">
                            <button type="button" id="cancelEdit">Cancel</button>
                            <button type="submit">Save</button>
                        </div>
                    </form>
                </div>
            </div>
        `).appendTo('body').show();
        
        // Close modal when clicking outside
        modal.click(function(e) {
            if (e.target === this) modal.remove();
        });
        
        // Cancel button
        modal.find('#cancelEdit').click(function() {
            modal.remove();
        });
        
        // Form submission
        modal.find('#editForm').submit(function(e) {
            e.preventDefault();
            
            $.ajax({
                url: 'entries.php',
                method: 'POST',
                data: {
                    action: 'update_entry',
                    id: entry.id,
                    title: $('#editTitle').val(),
                    comment: $('#editComment').val()
                },
                dataType: 'json',
                success: function(data) {
                    if (data.success) {
                        modal.remove();
                        loadAdminEntries(adminCurrentPage);
                    } else {
                        alert(data.message);
                    }
                },
                error: function(xhr) {
                    alert('Failed to update entry: ' + xhr.statusText);
                }
            });
        });
    }

    function escapeHtml(unsafe) {
        return unsafe
            .replace(/&/g, "&amp;")
            .replace(/</g, "&lt;")
            .replace(/>/g, "&gt;")
            .replace(/"/g, "&quot;")
            .replace(/'/g, "&#039;");
    }
});