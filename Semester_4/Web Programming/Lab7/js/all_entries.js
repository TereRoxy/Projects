$(document).ready(function() {
    // Configuration
    const config = {
        perPage: 4,
        container: '#entriesContainer',
        pageInfo: '#pageInfo',
        prevBtn: '#prevPage',
        nextBtn: '#nextPage'
    };
    
    // State
    const state = {
        currentPage: 1,
        totalPages: 1
    };
    
    // Initialize
    init();
    
    function init() {
        loadEntries(state.currentPage);
        setupEventHandlers();
    }
    
    function setupEventHandlers() {
        // Pagination controls
        $(config.prevBtn).on('click', function() {
            if (state.currentPage > 1) {
                state.currentPage--;
                loadEntries(state.currentPage);
            }
        });
        
        $(config.nextBtn).on('click', function() {
            if (state.currentPage < state.totalPages) {
                state.currentPage++;
                loadEntries(state.currentPage);
            }
        });
    }
    
    function loadEntries(page) {
        showLoading();
        
        $.ajax({
            url: 'entries.php',
            method: 'GET',
            dataType: 'json',
            data: {
                page: page,
                perPage: config.perPage,
            },
            success: function(data) {
                if (data.success) {
                    renderEntries(data.entries);
                    updatePagination(data);
                } else {
                    showError(data.message);
                }
            },
            error: function(xhr) {
                showError(xhr.statusText);
            }
        });
    }
    
    function renderEntries(entries) {
        if (entries.length === 0) {
            $(config.container).html('<p class="empty">No entries found.</p>');
            return;
        }
        
        let html = '';
        $.each(entries, function(i, entry) {
            html += `
                <div class="entry" data-id="${entry.id}">
                    <h3 class="entry-title">${escapeHtml(entry.title)}</h3>
                    <div class="entry-meta">
                        <span class="entry-author">${escapeHtml(entry.author_email)}</span>
                    </div>
                    <div class="entry-comment">${escapeHtml(entry.comment)}</div>
                </div>
            `;
        });
        
        $(config.container).html(html);
    }
    
    function updatePagination(data) {
        state.totalPages = data.totalPages;
        
        $(config.pageInfo).text(`Page ${data.page} of ${data.totalPages}`);
        $(config.prevBtn).prop('disabled', data.page <= 1);
        $(config.nextBtn).prop('disabled', data.page >= data.totalPages);
    }
    
    function showLoading() {
        $(config.container).html('<div class="loading">Loading entries...</div>');
    }
    
    function showError(message) {
        $(config.container).html(`<p class="error">Error: ${message}</p>`);
    }
    
    function escapeHtml(text) {
        return text.toString()
            .replace(/&/g, '&amp;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/"/g, '&quot;')
            .replace(/'/g, '&#039;');
    }
    
    function formatDate(dateString) {
        const date = new Date(dateString);
        return date.toLocaleDateString() + ' ' + date.toLocaleTimeString();
    }
});