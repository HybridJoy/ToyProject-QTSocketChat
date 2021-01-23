#include "Client.h"

#include <QWidget>
#include <QBoxLayout>
#include <QStackedWidget>

#include <QSize>
#include <QFont>
#include <QColor>

#include <QLabel>
#include <QSpinBox>
#include <QTextEdit>
#include <QLineEdit>

#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>

#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QWebSocket>
#include <QCoreApplication>

#define WINDOWHEIGHT			600
#define WINDOWWIDTH				800

#define MESSAGE_FONT_1			"Microsoft YaHei UI"
#define MESSAGE_FONT_2			"Buxton Sketch"
#define MESSAGE_FONT_SIZE		15
#define MESSAGE_FONT_COLOR_1	134, 212, 56
#define MESSAGE_FONT_COLOR_2	212, 56, 134
#define MESSAGE_FONT_COLOR_3	14, 156, 112
#define MESSAGE_FONT_COLOR_4	89, 64, 125 

#define DEFAULT_SERVER			"127.0.0.1"
#define DEFAULT_PORT			"1234"

#define CONNECT_LAYOUT			0
#define INTER_CLIENT_LAYOUT		1

#define SEND_MESSAGE_TYPE		1
#define CLIENT_MESSAGE_TYPE		2 
#define SERVER_MESSAGE_TYPE		3  

Client::Client(QWidget *parent)
	: QWidget(parent)
{
	this->resize(QSize(WINDOWWIDTH, WINDOWHEIGHT));
	this->setUI();
}

void Client::setUI()
{
	QButtonGroup * button_group = new QButtonGroup;
	button_group->setExclusive(true);

	//// connect interface /////

	// layout1
	QLabel * connect_server_Label = new QLabel("connect server");
	QPushButton * default_server_Button = new QPushButton("default");
	default_server_Button->setFixedWidth(WINDOWWIDTH / 8);

	QHBoxLayout *  connect_Layout_1 = new QHBoxLayout;
	connect_Layout_1->addWidget(connect_server_Label);
	connect_Layout_1->addWidget(default_server_Button);
	

	// layout2
	QLabel * ip_Label = new QLabel("ip address");
	ip_Label->setFixedWidth(WINDOWWIDTH / 8);
	ip_Label->setFixedHeight(WINDOWHEIGHT / 20);
	ip_Label->setAlignment(Qt::AlignCenter);
	ip_LineEdit = new QLineEdit;
	ip_LineEdit->setFixedWidth(3 * WINDOWWIDTH / 16);
	ip_LineEdit->setFixedHeight(WINDOWHEIGHT / 20);
	QLabel * port_Label = new QLabel("port");
	port_Label->setFixedWidth(WINDOWWIDTH / 16);
	port_Label->setFixedHeight(WINDOWHEIGHT / 20);
	port_Label->setAlignment(Qt::AlignCenter);
	port_SpinBox = new QSpinBox;
	port_SpinBox->setRange(0, 65535);
	port_SpinBox->setFixedWidth(WINDOWWIDTH / 8);
	port_SpinBox->setFixedHeight(WINDOWHEIGHT / 20);
	connect_Button = new QPushButton("connect");
	disconnect_Button = new QPushButton("disconnect");
	connect_Button->setFixedWidth(WINDOWWIDTH / 6);
	disconnect_Button->setFixedWidth(WINDOWWIDTH / 6);
	connect_Button->setFixedHeight(WINDOWHEIGHT / 16);
	disconnect_Button->setFixedHeight(WINDOWHEIGHT / 16);
	
	connect_Button->setCheckable(true);
	disconnect_Button->setCheckable(true);
	button_group->addButton(connect_Button, 0);
	button_group->addButton(disconnect_Button, 1);
	
	QHBoxLayout * connect_Layout_2 = new QHBoxLayout;
	connect_Layout_2->addWidget(ip_Label);
	connect_Layout_2->addWidget(ip_LineEdit);
	connect_Layout_2->addWidget(port_Label);
	connect_Layout_2->addWidget(port_SpinBox);
	connect_Layout_2->addWidget(connect_Button);
	connect_Layout_2->addWidget(disconnect_Button);

	// layout3
	QLabel * connect_client_Label = new QLabel("connect client");
	QHBoxLayout * connect_Layout_3 = new QHBoxLayout;
	connect_Layout_3->addWidget(connect_client_Label);

	// layout4
	client1_Button = new QPushButton("clientA");
	client2_Button = new QPushButton("clientB");
	client3_Button = new QPushButton("clientC");
	client4_Button = new QPushButton("clientD");
	group_Chat_Button = new QPushButton("Group Chat");
	
	link_Button = new QPushButton("link");
	link_Button->setFixedWidth(WINDOWWIDTH / 5);
	link_Button->setFixedHeight(WINDOWHEIGHT / 13);

	client1_Button->setFixedWidth(WINDOWWIDTH / 6);
	client2_Button->setFixedWidth(WINDOWWIDTH / 6);
	client3_Button->setFixedWidth(WINDOWWIDTH / 6);
	client4_Button->setFixedWidth(WINDOWWIDTH / 6);
	group_Chat_Button->setFixedWidth(WINDOWWIDTH / 6);
	client1_Button->setFixedHeight(WINDOWHEIGHT / 16);
	client2_Button->setFixedHeight(WINDOWHEIGHT / 16);
	client3_Button->setFixedHeight(WINDOWHEIGHT / 16);
	client4_Button->setFixedHeight(WINDOWHEIGHT / 16);
	group_Chat_Button->setFixedHeight(WINDOWHEIGHT / 16);
	

	client1_Button->setCheckable(true);
	client2_Button->setCheckable(true);
	client3_Button->setCheckable(true);
	client4_Button->setCheckable(true);
	group_Chat_Button->setCheckable(true);
	button_group->addButton(client1_Button);
	button_group->addButton(client2_Button);
	button_group->addButton(client3_Button);
	button_group->addButton(client4_Button);
	button_group->addButton(group_Chat_Button);

	QHBoxLayout * connect_Layout_4 = new QHBoxLayout;
	connect_Layout_4->addWidget(client1_Button);
	connect_Layout_4->addWidget(client2_Button);
	connect_Layout_4->addWidget(client3_Button);
	connect_Layout_4->addWidget(client4_Button);
	connect_Layout_4->addWidget(group_Chat_Button);
	connect_Layout_4->addWidget(link_Button);

	// layout5
	QLabel * receive_message_Label = new QLabel("message from server");
	QHBoxLayout * connect_Layout_5 = new QHBoxLayout;
	connect_Layout_5->addWidget(receive_message_Label);

	// layout6
	receive_server_message_TextEdit = new QTextEdit;
	receive_server_message_TextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // set the Vertical ScrollBar
	receive_server_message_TextEdit->setReadOnly(true);
	QHBoxLayout * connect_Layout_6 = new QHBoxLayout;
	connect_Layout_6->addWidget(receive_server_message_TextEdit);

	// layout7
	QPushButton * clear_Button = new QPushButton("clear");
	clear_Button->setFixedWidth(WINDOWWIDTH / 8);
	clear_Button->setFixedHeight(WINDOWHEIGHT / 16);
	QLabel * empty_Label = new QLabel();
	empty_Label->setFixedWidth(5 * WINDOWWIDTH / 8);
	empty_Label->setFixedHeight(WINDOWHEIGHT / 16);
	QLabel * log_write_Label = new QLabel("Log Write");
	log_write_Label->setFixedWidth(WINDOWWIDTH / 8);
	log_write_Label->setFixedHeight(WINDOWHEIGHT / 16);
	log_write_Label->setAlignment(Qt::AlignCenter);
	log_write_Radiobutton = new QRadioButton();
	log_write_Radiobutton->setChecked(true);
	log_write_Radiobutton->setFixedSize(QSize(WINDOWWIDTH / 8, WINDOWHEIGHT / 16));

	QHBoxLayout * connect_Layout_7 = new QHBoxLayout;
	connect_Layout_7->addWidget(clear_Button);
	connect_Layout_7->addWidget(empty_Label);
	connect_Layout_7->addWidget(log_write_Label);
	connect_Layout_7->addWidget(log_write_Radiobutton);

	// VLayout
	QVBoxLayout * connect_Layout = new QVBoxLayout;
	connect_Layout->addLayout(connect_Layout_1, 0.5);
	connect_Layout->addLayout(connect_Layout_2, 2);
	connect_Layout->addLayout(connect_Layout_3, 0.5);
	connect_Layout->addLayout(connect_Layout_4, 2);
	connect_Layout->addLayout(connect_Layout_5, 0.5);
	connect_Layout->addLayout(connect_Layout_6, 4);
	connect_Layout->addLayout(connect_Layout_7, 1);

	//// Inter-client communication interface ////

	float width  = this->frameGeometry().width();
	float height = this->frameGeometry().height();

	client_name_Label = new QPushButton();
	client_name_Label->setFixedHeight(height / 8);
	client_name_Label->setEnabled(false);
	return_Button = new QPushButton("Return");
	return_Button->setFixedHeight(height / 8);

	receive_client_message_TextEdit = new QTextEdit;
	receive_client_message_TextEdit->setFixedHeight(6 * height / 8);
	receive_client_message_TextEdit->setCurrentFont(QFont(MESSAGE_FONT_1, MESSAGE_FONT_SIZE));


	receive_client_message_TextEdit->setReadOnly(true);
	send_client_message_TextEdit = new QTextEdit;
	send_client_message_TextEdit->setFixedHeight(height / 8);

	QPushButton * send_client_message_Button = new QPushButton("Send");
	send_client_message_Button->setFixedHeight(height / 8);
	
	QPushButton * record_Button = new QPushButton("Communication Record");
	record_Button->setFixedHeight(height / 8);
	record_Button->setEnabled(false);

	record_TextEdit = new QTextEdit;
	record_TextEdit->setReadOnly(true);

	QPushButton * reset_Button = new QPushButton("Reset");
	reset_Button->setFixedHeight(height / 8);

	QGridLayout * inter_client_commu_Layout = new QGridLayout;
	inter_client_commu_Layout->addWidget(client_name_Label, 0, 0, 1, 6);
	inter_client_commu_Layout->addWidget(return_Button, 0, 0, 1, 1);
	inter_client_commu_Layout->addWidget(receive_client_message_TextEdit, 1, 0, 6, 6);
	inter_client_commu_Layout->addWidget(send_client_message_TextEdit, 7, 0, 1, 5);
	inter_client_commu_Layout->addWidget(send_client_message_Button, 7, 5, 1, 1);
	inter_client_commu_Layout->addWidget(record_Button, 0, 6, 1, 2);
	inter_client_commu_Layout->addWidget(record_TextEdit, 1, 6, 7, 2);
	inter_client_commu_Layout->addWidget(reset_Button, 7, 6, 1, 2);

	inter_client_commu_Layout->setMargin(0);
	inter_client_commu_Layout->setSpacing(1);

	stackwidget = new QStackedWidget;
	QWidget * widget[2];

	for (int i = 0; i < 2; i++)
	{
		widget[i] = new QWidget;
		widget[i]->resize(WINDOWWIDTH, WINDOWHEIGHT);
		if (i == 0)
		{
			widget[i]->setLayout(connect_Layout);
		}
		if (i == 1)
		{
			widget[i]->setLayout(inter_client_commu_Layout);
		}
		stackwidget->addWidget(widget[i]);
	}
	
	// set current Layout
	QGridLayout * mainLayout = new QGridLayout;
	mainLayout->addWidget(stackwidget);
	setLayout(mainLayout);

	this->setState(false);

	// initialize variable
	is_connected = false;
	log_write_state = true;
	client_ready = false;
	current_date_time = new QDateTime();
	client_socket = new QWebSocket();
	current_Layout_Index = CONNECT_LAYOUT;

	// create dir to save log and chat message history
	QString path = QCoreApplication::applicationDirPath();
	QDir * log_Dir = new QDir;
	log_Dir_path = QString("%1/log").arg(path);
	if (! log_Dir->exists(log_Dir_path))
	{
		if (log_Dir->mkdir(log_Dir_path))
		{
			this->receive_message("log dir create successfully!", SERVER_MESSAGE_TYPE);
	    }
		else
		{
			this->receive_message("log dir create failed!", SERVER_MESSAGE_TYPE);
		}
	}
	else
	{
		this->receive_message("log dir exist!", SERVER_MESSAGE_TYPE);
	}
	
	QDir * base_Dir = new QDir;
	QString base_Dir_path = QString("%1/chat record").arg(path);
	base_Dir->mkdir(base_Dir_path);

	QDir * chat_record_Dir = new QDir;
	chat_record_Dir_path = QString("%1/client").arg(base_Dir_path);
	if (!chat_record_Dir->exists(chat_record_Dir_path))
	{
		if (chat_record_Dir->mkdir(chat_record_Dir_path))
		{
			this->receive_message("chat record dir create successfully!", SERVER_MESSAGE_TYPE);
		}
		else
		{
			this->receive_message("chat record dir create failed!", SERVER_MESSAGE_TYPE);
		}
	}
	else
	{
		this->receive_message("chat record dir exist!", SERVER_MESSAGE_TYPE);
	}

	//// connect button / line / Text Edit ////

	connect(default_server_Button, &QPushButton::clicked, this, &Client::set_default_server);

	connect(connect_Button, &QPushButton::clicked, this, &Client::connect_server);
	connect(disconnect_Button, &QPushButton::clicked, this, &Client::disconnect_server);
	connect(client_socket, SIGNAL(connected()), this, SLOT(on_connected()));
	connect(client_socket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
	connect(client_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(receive_server_message(QString)));
	connect(send_client_message_Button, &QPushButton::clicked, this, &Client::send_message);

	// Choose the chat object / mode
	connect(client1_Button, &QPushButton::clicked, this, &Client::select_client);
	connect(client2_Button, &QPushButton::clicked, this, &Client::select_client);
	connect(client3_Button, &QPushButton::clicked, this, &Client::select_client);
	connect(client4_Button, &QPushButton::clicked, this, &Client::select_client);
	connect(group_Chat_Button, &QPushButton::clicked, this, &Client::select_client);

	connect(link_Button, &QPushButton::clicked, this, &Client::select_layout);
	connect(return_Button, &QPushButton::clicked, this, &Client::select_layout);
	connect(clear_Button, &QPushButton::clicked, this, &Client::clear_message_record);
	connect(reset_Button, &QPushButton::clicked, this, &Client::clear_message_record);

	// log write
	connect(log_write_Radiobutton, &QPushButton::clicked, this, &Client::log_write_state_change);

}

void Client::setState(bool state)
{
	ip_LineEdit->setEnabled(!state);
	port_SpinBox->setEnabled(!state);
	connect_Button->setEnabled(!state);
	disconnect_Button->setEnabled(state);
	client1_Button->setEnabled(state);
	client2_Button->setEnabled(state);
	client3_Button->setEnabled(state);
	client4_Button->setEnabled(state);
	group_Chat_Button->setEnabled(state);
	link_Button->setEnabled(state);
}

void Client::select_client()
{
	QPushButton * widget = static_cast<QPushButton*>(sender());
	if (widget == client1_Button)
	{
		client_ready = true;
		current_Commu_client = 1;
		client_name_Label->setText("ClientA");
	}
	if (widget == client2_Button)
	{
		client_ready = true;
		current_Commu_client = 2;
		client_name_Label->setText("ClientB");
	}
	if (widget == client3_Button)
	{
		client_ready = true;
		current_Commu_client = 3;
		client_name_Label->setText("ClientC");
	}
	if (widget == client4_Button)
	{
		client_ready = true;
		current_Commu_client = 4;
		client_name_Label->setText("ClientD");
	}
	if (widget == group_Chat_Button)
	{
		client_ready = true;
		current_Commu_client = 5;
		client_name_Label->setText("Group Chat");
	}
}

void Client::select_layout()
{
	QPushButton * widget = static_cast<QPushButton*>(sender());
	if ((widget == link_Button) && client_ready)
	{
		current_Layout_Index = INTER_CLIENT_LAYOUT;
		if (current_Commu_client != 5)
		{
			this->read_history_message();
		}	
	}
	if (widget == return_Button)
	{
		receive_client_message_TextEdit->clear();
		record_TextEdit->clear();
		current_Layout_Index = CONNECT_LAYOUT;
	}
	stackwidget->setCurrentIndex(current_Layout_Index);
}

void Client::set_default_server()
{
	ip_LineEdit->setText(DEFAULT_SERVER);
	port_SpinBox->setSpecialValueText(DEFAULT_PORT);
}

void Client::connect_server()
{
	QString path = QString("ws://%1:%2").arg(ip_LineEdit->text()).arg(port_SpinBox->text());
	QUrl url(path);
	client_socket->open(url);
}

void Client::disconnect_server()
{
	client_socket->close();
}

void Client::on_connected()
{
	QString path = QString("ws://%1:%2").arg(ip_LineEdit->text()).arg(port_SpinBox->text());

	is_first_message = true;
	is_connected = true;
	QString message;
	if (is_connected)
	{
		message = path + "\n        connect sussceessful";
		this->setState(true);
	}
	else
	{
		message = path + "\n        connect failed!";
	}
	this->receive_message(message, SERVER_MESSAGE_TYPE);
}

void Client::on_disconnected()
{
	QString message;
	if (is_connected == true)
	{
		is_connected = false;
		if (!is_connected)
		{
			message = "disconnect sussceessful";
			this->setState(false);
		}
		else
		{
			message = "disconnect failed!";
		}	
	}
	else
	{
		message = "connect failed!\nplease check the server whether is open ,or you can try again!";
	}
	this->receive_message(message, SERVER_MESSAGE_TYPE);
}

void Client::send_message()
{
	if (is_connected == true)
	{
		QString msg = send_client_message_TextEdit->toPlainText();
		send_client_message_TextEdit->clear();

		QString record;
		QString final_msg;
		if (current_Commu_client != 5)
		{
			final_msg = QString("from client %1 to %2 %3").arg(client_self).arg(current_Commu_client).arg(msg);
			this->write_history_message(final_msg);

			QString client_name = client_name_Label->text();
			record = "Local-->" + client_name;	
		}
		else
		{
			record = QString("client %1").arg(client_self);
			final_msg = QString("Group Chat : %1 : %2").arg(client_self).arg(msg);	
		}
		record_TextEdit->setAlignment(Qt::AlignHCenter);
		record_TextEdit->append(record);
		client_socket->sendTextMessage(final_msg);
		this->receive_message(msg, SEND_MESSAGE_TYPE);
	}
	else
	{
		receive_client_message_TextEdit->setAlignment(Qt::AlignHCenter);
		receive_client_message_TextEdit->setTextColor(QColor(Qt::black));
		receive_client_message_TextEdit->append("You are offline");
	}
}

void Client::receive_message(QString msg,int msg_type)
{
	QColor message_color;
	if (msg_type == SEND_MESSAGE_TYPE)
	{
		message_color = this->select_message_color(client_self);
		receive_client_message_TextEdit->setAlignment(Qt::AlignRight);
		receive_client_message_TextEdit->setTextColor(message_color);
		receive_client_message_TextEdit->append(msg + "\n");
	}
	if (msg_type == CLIENT_MESSAGE_TYPE)
	{
		if (current_Commu_client != 5)
		{
			message_color = this->select_message_color(current_Commu_client);
			receive_client_message_TextEdit->setAlignment(Qt::AlignLeft);
			receive_client_message_TextEdit->setTextColor(message_color);
			receive_client_message_TextEdit->append(msg + "\n");
		}
		else
		{
			int client = msg[0].toLatin1() - '0';
			message_color = this->select_message_color(client);

			receive_client_message_TextEdit->setAlignment(Qt::AlignLeft);
			receive_client_message_TextEdit->setCurrentFont(QFont(MESSAGE_FONT_2));
			receive_client_message_TextEdit->setTextColor(message_color);

			QString message = QString("Client %1\n").arg(msg[0]);
			receive_client_message_TextEdit->append(message);
			receive_client_message_TextEdit->setCurrentFont(QFont(MESSAGE_FONT_1, MESSAGE_FONT_SIZE));
			receive_client_message_TextEdit->append(msg.mid(3) + "\n\n");
		}	
	}
	if (msg_type == SERVER_MESSAGE_TYPE)
	{
		receive_server_message_TextEdit->setAlignment(Qt::AlignLeft);
		receive_server_message_TextEdit->append(msg);
		if (log_write_state == true)
		{
			this->log_write(msg);
		}
	}	
}

void Client::receive_server_message(QString msg)
{
	if (current_Layout_Index == CONNECT_LAYOUT)
	{
		if (is_first_message == true)
		{
			QChar client = msg[msg.length() - 1];
			client_self = client.toLatin1() - '0';
			// not allow link self
			switch (client_self)
			{
				case 1: client1_Button->setEnabled(false);
						break;
				case 2: client2_Button->setEnabled(false);
						break;
				case 3: client3_Button->setEnabled(false);
						break;
				case 4: client4_Button->setEnabled(false);
						break;
			}
			is_first_message = false;
		}
		// if current user doesn't open the commu layout
		if (msg.mid(0, 11) == "from client")
		{
			this->write_history_message(msg);
		}
		else if (msg.mid(0, 10) == "Group Chat")
		{
			// wait to add (Group Chat history)
		}
		else
		{
			this->receive_message(msg, SERVER_MESSAGE_TYPE);
		}
		
	}
	if (current_Layout_Index == INTER_CLIENT_LAYOUT)
	{
		QString record;
		if (current_Commu_client == 5)
		{
			record = QString("client %1").arg(msg[13]);
			this->receive_message(msg.mid(13), CLIENT_MESSAGE_TYPE);
		}
		else
		{
			QString client_name = client_name_Label->text();
			record = client_name + "-->Local";

			this->write_history_message(msg);

			// only to show the chat object's message
			QString judg = QString("from client %1 to %2").arg(current_Commu_client).arg(client_self);
			if (msg.mid(0, 18) == judg)
			{
				this->receive_message(msg.mid(18), CLIENT_MESSAGE_TYPE);
			}
		}
		record_TextEdit->setAlignment(Qt::AlignHCenter);
		record_TextEdit->append(record);
	}
}

void Client::clear_message_record()
{
	if (current_Layout_Index == CONNECT_LAYOUT)
	{
		receive_server_message_TextEdit->clear();
	}
	if (current_Layout_Index == INTER_CLIENT_LAYOUT)
	{
		receive_client_message_TextEdit->clear();
		record_TextEdit->clear();
	}
}

void Client::write_history_message(QString msg)
{
	QString record_file_name = QString("%1/client_commu_record_%2.txt").arg(chat_record_Dir_path).arg(client_self);
	QFile file(record_file_name);
	if (!(file.open(QIODevice::Append | QIODevice::Text)))
	{
		receive_server_message_TextEdit->setAlignment(Qt::AlignLeft);
		receive_server_message_TextEdit->append("history message file open failed!");
		return;
	}
	else
	{
		QTextStream outfile(&file);
		outfile << msg << endl;
	}
	file.close();
}

void Client::read_history_message()
{
	QString record_file_name = QString("%1/client_commu_record_%2.txt").arg(chat_record_Dir_path).arg(client_self);
	QFile file(record_file_name);
	if (!(file.open(QIODevice::ReadOnly | QIODevice::Text)))
	{
		receive_server_message_TextEdit->setAlignment(Qt::AlignLeft);
		receive_server_message_TextEdit->append("history message file open failed!");
		return;
	}
	else
	{
		QTextStream infile(&file);
		QString line = infile.readLine();
		while (!line.isNull())
		{
			QString message(line);
			QString judg_1 = QString("from client %1 to %2").arg(current_Commu_client).arg(client_self);
			QString judg_2 = QString("from client %1 to %2").arg(client_self).arg(current_Commu_client);
			if (message.mid(0, 18) == judg_1)
			{
				this->receive_message(message.mid(18), CLIENT_MESSAGE_TYPE);
			}
			if (message.mid(0, 18) == judg_2)
			{
				this->receive_message(message.mid(18), SEND_MESSAGE_TYPE);
			}
			line = infile.readLine();
		}
	}
	file.close();
}

QColor Client::select_message_color(int client)
{
	QColor message_color;
	switch (client)
	{
		case 1:  message_color = QColor(MESSAGE_FONT_COLOR_1);
				 break;
		case 2:  message_color = QColor(MESSAGE_FONT_COLOR_2);
				 break;
		case 3:  message_color = QColor(MESSAGE_FONT_COLOR_3);
			     break;
		case 4:  message_color = QColor(MESSAGE_FONT_COLOR_4);
				 break;
	}
	return message_color;
}

void Client::log_write(QString msg)
{
	QString log_file_name = QString("%1/client_%2.log").arg(log_Dir_path).arg(client_self);
	QFile file(log_file_name);
	if (!(file.open(QIODevice::Append | QIODevice::Text)))
	{
		receive_server_message_TextEdit->setAlignment(Qt::AlignLeft);
		receive_server_message_TextEdit->append("log file open failed!");
		return;
	}
	else
	{
		QTextStream outfile(&file);
		QString time = current_date_time->currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
		outfile << time << endl;
		outfile << "        " << msg << endl;
	}
	file.close();
}

void Client::log_write_state_change()
{
	log_write_state = log_write_Radiobutton->isChecked();
	if (log_write_state == true)
	{
		this->receive_message("log write is open!", SERVER_MESSAGE_TYPE);
	}
	if (log_write_state == false)
	{
		this->receive_message("log write is close!", SERVER_MESSAGE_TYPE);
	}
}
