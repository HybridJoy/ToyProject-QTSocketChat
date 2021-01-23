#pragma once

#include <QtWidgets/QWidget>

#define MAX_CLIENT	4

class QSpinBox;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QRadioButton;

class QDateTime;
class QWebSocket;
class QWebSocketServer;

class Server : public QWidget
{
	Q_OBJECT

public:
	Server(QWidget *parent = Q_NULLPTR);
	void setUI();
	void set_default_port();

	void start_server();
	void stop_server();

	void receive_message(QString);
	void clear_message_record();

	void transmit_store_message(int);
	void store_message_not_transmit(QString,int);
	
	void log_write(QString);
	void log_write_state_change();

private Q_SLOTS:
	void new_connection();
	void client_disconnect();
	void receive_client_message(QString);

private:
	bool log_write_state;
	int current_client_num;
	int clients_state[MAX_CLIENT];
	QString log_Dir_path;
	QString chat_record_Dir_path;

	QDateTime  * current_date_time;
	QWebSocket * client_socket;
	QWebSocket * clients[MAX_CLIENT];
	QWebSocketServer * server_socket;
	
	QPushButton * client1_Button;
	QPushButton * client2_Button;
	QPushButton * client3_Button;
	QPushButton * client4_Button;

	QLineEdit * ip_LineEdit;
	QSpinBox  * port_SpinBox;
	QTextEdit * receive_client_message_TextEdit;

	QPushButton  * start_server_Button;
	QPushButton  * stop_server_Button;
	QPushButton  * default_port_Button;
	QRadioButton * log_write_Radiobutton;	
};
