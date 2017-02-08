function populate_shares(xml) {
    var xmldoc = $.parseXML(xml);
    var $xml = $(xmldoc);
    $.each($xml.find("Share"), function(i, share) {
        var volume_name = share.getAttribute("resource-id").split('/')[0];
        var share_name = share.getAttribute("share-name");
        var is_audit = share.getAttribute("used-by-sample3");
        var $newdiv = $('<input id="cb-' + i +
                        '" volume-name="' + volume_name +
                        '" share-name="' + share_name +
                        '" type="checkbox" ' + (is_audit ? 'checked' : '') + '>'
                        + share_name + '</input><br/>');
        $('#shares').append($newdiv);
    });
}

$(document).ready(function() {
    jQuery.ajax({
        url: 'get-shares.php',
        success: function(result) {
            populate_shares(result)
        },
        async: false
    }); 

    $('#apply').click(function() {
        var audit_opts = "";
        $.each($('#shares input'), function(i, share) {
            if (audit_opts!="")
                audit_opts += "&";
            var id = share.getAttribute("id");
            var volume_name = share.getAttribute("volume-name");
            var share_name = share.getAttribute("share-name");
            var is_audit = $('#' + id).attr('checked');
            audit_opts += volume_name + '%2F' + share_name + '=' + (is_audit ? "1" : "0");
        });
        jQuery.ajax({
            url: 'set-audit.php?' + audit_opts,
            async: false
        }); 
    });
});

