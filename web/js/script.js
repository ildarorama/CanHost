

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

    $("#loadbtn").click(function () {
        $.get("/scripts/testscript.cpp",
            function(data) {
                $("#editField").val(data);
            });
    });

    $("#savebtn").click(function () {
        var con=$("#editField").val();
        $.ajax({
            dataType: "json",
            method: 'POST',
            url: "http://localhost:8080/api",
            data: JSON.stringify({query: "saveScript", script: "testscript.cpp",content: con}),
            success: function(e) { alert(e); }
        });

    });



});