#pragma once

#include <QtWidgets/QWidget>

class QDateTime;
class QWebSocket;

class QSpinBox;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QRadioButton;
class QStackedWidget;

class Client : public QWidget
{
	Q_OBJECT

public:
	Client(QWidget *parent = Q_NULLPTR);

	void setUI();
	void setState(bool);
	void select_client();
	void select_layout();
	void set_default_server();
	QColor select_message_color(int);

	void connect_server();
	void disconnect_server();
	void send_message();
	void receive_message(QString,int);

	void clear_message_record();
	void read_history_message();
	void write_history_message(QString);

	void log_write(QString);
	void log_write_state_change();

private Q_SLOTS:
	void on_connected();
	void on_disconnected();
	void receive_server_message(QString);

private:
	int client_self;
	int current_Commu_client;
	int current_Layout_Index;
	bool client_ready;
	bool is_connected;
	bool is_first_message;
	bool log_write_state;
	QString log_Dir_path;
	QString chat_record_Dir_path;

	QWebSocket * client_socket;
	QDateTime  * current_date_time;

	QLineEdit * ip_LineEdit;
	QSpinBox  * port_SpinBox;

	QPushButton * connect_Button;
	QPushButton * disconnect_Button;

	// choose chat type
	QPushButton * client1_Button;
	QPushButton * client2_Button;
	QPushButton * client3_Button;
	QPushButton * client4_Button;
	QPushButton * group_Chat_Button;

	QPushButton  * link_Button;
	QPushButton  * return_Button;
	QPushButton  * client_name_Label;
	QRadioButton * log_write_Radiobutton;

	QTextEdit * record_TextEdit;
	QTextEdit * send_client_message_TextEdit;
	QTextEdit * receive_client_message_TextEdit;
	QTextEdit * receive_server_message_TextEdit;
	
	// Layout manager
	QStackedWidget * stackwidget;
	
};
