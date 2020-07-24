void get_drive(int id) {
  memset(request_buffer, NULL, 1); //reblank the buffer
  memset(response_buffer, NULL, 1); //reblank the buffer

  sprintf(request_buffer, "GET http://ireneterpstra.pythonanywhere.com/controller?id=%d HTTP/1.1\r\n", id);
  strcat(request_buffer, "Host: ireneterpstra.pythonanywhere.com\r\n"); //add more to the end
  strcat(request_buffer, "Content-Type: application/x-www-form-urlencoded\r\n");
  strcat(request_buffer, "\r\n"); //add blank line!
  //submit to function that performs GET.  It will return output using response_buffer char array
  do_http_request("ireneterpstra.pythonanywhere.com", request_buffer, response_buffer, OUT_BUFFER_SIZE, RESPONSE_TIMEOUT, true);
  Serial.println(response_buffer); //print to serial monitor

  memset(output, NULL, 1);
  strcat(output, response_buffer);
  //  strncpy(date, response_buffer, 10);
}

uint8_t char_append(char* buff, char c, uint16_t buff_size) {
  int len = strlen(buff);
  if (len > buff_size) return false;
  buff[len] = c;
  buff[len + 1] = '\0';
  return true;
}

void do_http_request(char* host, char* request, char* response, uint16_t response_size, uint16_t response_timeout, uint8_t serial) {
  WiFiClient client; //instantiate a client object
  if (client.connect(host, 80)) { //try to connect to host on port 80
    if (serial) Serial.print(request);//Can do one-line if statements in C without curly braces
    client.print(request);
    memset(response, 0, response_size); //Null out (0 is the value of the null terminator '\0') entire buffer
    uint32_t count = millis();
    while (client.connected()) { //while we remain connected read out data coming back
      client.readBytesUntil('\n', response, response_size);
      if (serial) Serial.println(response);
      if (strcmp(response, "\r") == 0) { //found a blank line!
        break;
      }
      memset(response, 0, response_size);
      if (millis() - count > response_timeout) break;
    }
    memset(response, 0, response_size);
    count = millis();
    while (client.available()) { //read out remaining text (body of response)
      char_append(response, client.read(), OUT_BUFFER_SIZE);
    }
    if (serial) Serial.println(response);
    client.stop();
    if (serial) Serial.println("-----------");
  } else {
    if (serial) Serial.println("connection failed :/");
    if (serial) Serial.println("wait 0.5 sec...");
    client.stop();
  }
}