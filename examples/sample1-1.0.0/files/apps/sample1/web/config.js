$(document).ready(function() {
    $('#apply').hide()
    $('#select-interval').change(function() {
        value = $('#select-interval option:selected').attr('value');
        if (value < 1)
            $('#apply').hide()
        else
            $('#apply').show()
    }); 
    $('#apply').click(function() {
        jQuery.ajax({
            url: 'set-config.php?interval=' + $('#select-interval option:selected').attr('value'),
            success: function(result) {
                $('#apply').hide()
            },
            async: false
        }); 
    });
});

