# Writes everything the Arduino prints on the serial port into a log file
# (and to the console). Usage: .\log_serial.ps1 -Port COM3
param(
    [Parameter(Mandatory = $true)][string]$Port,
    [int]$Baud = 9600,
    [string]$LogFile = (Join-Path $PSScriptRoot "logs\test_log_$(Get-Date -Format 'yyyyMMdd_HHmmss').txt")
)

New-Item -ItemType Directory -Force (Split-Path $LogFile) | Out-Null
$serial = New-Object System.IO.Ports.SerialPort $Port, $Baud
$serial.Open()
Write-Host "Logging $Port to $LogFile (Ctrl+C to stop)"
try {
    while ($true) {
        $line = $serial.ReadLine().TrimEnd()
        Write-Host $line
        Add-Content -Path $LogFile -Value $line
    }
} finally {
    $serial.Close()
}
