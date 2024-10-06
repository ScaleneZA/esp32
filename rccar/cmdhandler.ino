
static esp_err_t cmd_handler(httpd_req_t *req){
  char*  buf;
  size_t buf_len;
  char variable[32] = {0,};
  
  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    buf = (char*)malloc(buf_len);
    if(!buf){
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
      if (httpd_query_key_value(buf, "go", variable, sizeof(variable)) == ESP_OK) {
      } else {
        free(buf);
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
    } else {
      free(buf);
      httpd_resp_send_404(req);
      return ESP_FAIL;
    }
    free(buf);
  } else {
    httpd_resp_send_404(req);
    return ESP_FAIL;
  }

  sensor_t * s = esp_camera_sensor_get();
  //flip the camera vertically
  s->set_vflip(s, 1);          // 0 = disable , 1 = enable
  // mirror effect
  s->set_hmirror(s, 1);          // 0 = disable , 1 = enable

  int res = 0;
  
  if(!strcmp(variable, "up")) {
    Serial.print("Going Forward");
    analogWrite(DRIVE_R, 0);
    analogWrite(DRIVE_F, 255);
  } else if(!strcmp(variable, "left")) {
    Serial.print("Turning Left");
    analogWrite(STEER_R, 0);
    analogWrite(STEER_L, 255);
  } else if(!strcmp(variable, "right")) {
    Serial.print("Turning Right");
    analogWrite(STEER_L, 0);
    analogWrite(STEER_R, 255);
  } else if(!strcmp(variable, "down")) {
    Serial.print("Reversing");
    analogWrite(DRIVE_F, 0);
    analogWrite(DRIVE_R, 255);
  } else if(!strcmp(variable, "up-stop")) {
    Serial.print("Breaking");
    analogWrite(DRIVE_F, 0);
    analogWrite(DRIVE_R, 0);
  } else if(!strcmp(variable, "left-stop")) {
    Serial.print("Turning Straight");
    analogWrite(STEER_L, 0);
    analogWrite(STEER_R, 0);
  } else if(!strcmp(variable, "right-stop")) {
    Serial.print("Turning Straight");
    analogWrite(STEER_L, 0);
    analogWrite(STEER_R, 0);
  } else if(!strcmp(variable, "down-stop")) {
    Serial.print("Breaking");
    analogWrite(DRIVE_F, 0);
    analogWrite(DRIVE_R, 0);
  } else {
    res = -1;
  }

  if(res){
    return httpd_resp_send_500(req);
  }

  httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
  return httpd_resp_send(req, NULL, 0);
}
