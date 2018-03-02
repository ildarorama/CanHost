

$(function() {
    $("#testbtn").click(function () {
        $.ajax({
            dataType: "json",
            method: 'POST',
            url: "http://localhost:8081/api",
            data: JSON.stringify({test: "mytest"}),
            success: function(e) { alert(e); }
        });
    });
});