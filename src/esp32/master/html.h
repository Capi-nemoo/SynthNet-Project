const char* HTML_PAGE = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Instant Weather Checker</title>
    <script>
    function submitCityName() {
        var cityName = document.getElementById('cityInput').value;
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById('result').innerHTML = this.responseText;
            }
        };
        xhttp.open("GET", "/submit?cityName=" + cityName, true);
        xhttp.send();
        return false; // Importante para evitar que el formulario envíe de la forma predeterminada.
    }
    </script>
</head>
<body>
    <h1>Instant Weather Checker</h1>
    <form onsubmit="return submitCityName();">
        <input type="text" id="cityInput" name="cityName" placeholder="Enter a city name for weather info" size="30">
        <input type="submit" value="Submit">
    </form>
    <div id="result">Result will be shown here</div>
</body>
</html>
)rawliteral";