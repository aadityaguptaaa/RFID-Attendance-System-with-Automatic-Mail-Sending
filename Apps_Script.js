// Created By Aaditya Gupta

var ss = SpreadsheetApp.openById('nsdcjsdncdjncsndckdsmk'); // Enter your Google Sheets URL Id here
var sheet = ss.getSheetByName('Sheet1');

function doGet(e) {
  Logger.log(JSON.stringify(e));
  
  if (!e || !e.parameters || !e.parameters.name) {
    return ContentService.createTextOutput("Received data is undefined");
  }
  
  var Curr_Date = new Date();
  var Curr_Time = Curr_Date.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' }); // Get time in HH:mm format
  var name = stripQuotes(e.parameters.name);
  
  var nextRow = sheet.getLastRow() + 1;
  sheet.getRange("A" + nextRow).setValue(Curr_Date); // Store full date in column A
  sheet.getRange("B" + nextRow).setValue(Curr_Time); // Store time in column B
  sheet.getRange("C" + nextRow).setValue(name); // Store name in column C

  return ContentService.createTextOutput("Card holder name is stored in column C");
}

function stripQuotes(value) {
  return value.toString().replace(/^["']|['"]$/g, "");
}

function sendAttendanceData() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var data = sheet.getRange(2, 1, sheet.getLastRow() - 1, 3).getValues(); // Get attendance data from first three columns
  
  // Start building the HTML email body
  var emailBody = "<h2>Attendance Data</h2>";
  emailBody += "<table border='1' style='border-collapse:collapse;'>";
  emailBody += "<tr><th>Date</th><th>Time</th><th>Name</th></tr>"; // Table headers

  // Loop through data and format it for email
  for (var i = 0; i < data.length; i++) {
    emailBody += "<tr>";
    emailBody += "<td>" + Utilities.formatDate(new Date(data[i][0]), Session.getScriptTimeZone(), "dd/MM/yyyy") + "</td>"; // Format date
    emailBody += "<td>" + data[i][1] + "</td>"; // Keep time in HH:mm format
    emailBody += "<td>" + data[i][2] + "</td>";
    emailBody += "</tr>";
  }

  emailBody += "</table>"; // End of table

  // Email details
  var subject = "Automated RFID Attendance Report";
  var recipient = "xxxx@gmail.com"; // *Replace with faculty's email address*

  // Send the email with HTML content
  MailApp.sendEmail({
    to: recipient,
    subject: subject,
    htmlBody: emailBody
  });
}

function scheduleEmail() {
  ScriptApp.newTrigger("sendAttendanceData")
    .timeBased()
    .everyDays(1)  // Sends the email daily; you can modify the schedule
    .atHour(11)    // Sets the hour (20 = 8 PM)
    .atMinute(49)  // Sets the minute (25 minutes past the hour)
    .create();
}
