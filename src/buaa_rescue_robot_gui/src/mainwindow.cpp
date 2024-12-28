#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize ROS2 node
    node = std::make_shared<rclcpp::Node>("buaa_rescue_robot_gui");

    // Initialize publishers
    slave_control_topic_publisher_1 = node->create_publisher<buaa_rescue_robot_msgs::msg::ControlMessageSlave>(
        "slave_control_topic_1", 10);
    gripper_control_topic_publisher_1 = node->create_publisher<buaa_rescue_robot_msgs::msg::ControlMessageSlaveGripper>(
        "gripper_control_topic_1", 10);
    master_control_topic_publisher = node->create_publisher<buaa_rescue_robot_msgs::msg::ControlMessageMaster>(
        "master_control_topic", 10);
    joint_space_topic_publisher = node->create_publisher<std_msgs::msg::Float64MultiArray>(
        "joint_space_topic", 10);

    // Initialize models for sensor displays
    SensorsMessageDisplay_1 = new QStringListModel(this);
    SensorsMessageDisplay_3 = new QStringListModel(this);
    SensorsMessageDisplay_4 = new QStringListModel(this);
    SensorsMessageDisplay_5 = new QStringListModel(this);
    SensorsMessageDisplay_6 = new QStringListModel(this);

    // Set models for list views
    ui->SensorsMessageDisplay_1->setModel(SensorsMessageDisplay_1);
    ui->SensorsMessageDisplay_3->setModel(SensorsMessageDisplay_3);
    ui->SensorsMessageDisplay_4->setModel(SensorsMessageDisplay_4);
    ui->SensorsMessageDisplay_5->setModel(SensorsMessageDisplay_5);
    ui->SensorsMessageDisplay_6->setModel(SensorsMessageDisplay_6);

    // Store controls in vectors for easier access
    thetaControls = {
        ui->robomaster1_theta_1,
        ui->robomaster1_theta_2,
        ui->robomaster1_theta_3,
        ui->robomaster1_theta_4,
        ui->robomaster1_theta_5,
        ui->robomaster1_theta_6};

    speedControls_robomaster1 = {
        ui->robomaster1_snake_motor_speed_control_1,
        ui->robomaster1_snake_motor_speed_control_2,
        ui->robomaster1_snake_motor_speed_control_3,
        ui->robomaster1_snake_motor_speed_control_4,
        ui->robomaster1_snake_motor_speed_control_5,
        ui->robomaster1_snake_motor_speed_control_6,
        ui->robomaster1_snake_motor_speed_control_7,
        ui->robomaster1_snake_motor_speed_control_8,
        ui->robomaster1_snake_motor_speed_control_9,
        ui->robomaster1_snake_motor_speed_control_10,
        ui->robomaster1_snake_motor_speed_control_11,
        ui->robomaster1_snake_motor_speed_control_12};

    positionControls_robomaster1 = {
        ui->robomaster1_snake_motor_position_control_1,
        ui->robomaster1_snake_motor_position_control_2,
        ui->robomaster1_snake_motor_position_control_3,
        ui->robomaster1_snake_motor_position_control_4,
        ui->robomaster1_snake_motor_position_control_5,
        ui->robomaster1_snake_motor_position_control_6,
        ui->robomaster1_snake_motor_position_control_7,
        ui->robomaster1_snake_motor_position_control_8,
        ui->robomaster1_snake_motor_position_control_9,
        ui->robomaster1_snake_motor_position_control_10,
        ui->robomaster1_snake_motor_position_control_11,
        ui->robomaster1_snake_motor_position_control_12};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_publishButton_clicked()
{
    // Create and publish slave control message
    auto slave_msg = buaa_rescue_robot_msgs::msg::ControlMessageSlave();
    for (size_t i = 0; i < speedControls_robomaster1.size(); ++i)
    {
        slave_msg.snake_speed_control_array[i] = speedControls_robomaster1[i]->value();
        slave_msg.snake_position_control_array[i] = positionControls_robomaster1[i]->value();
    }
    slave_msg.robomaster_mode = ui->robomaster1_mode->value();
    slave_control_topic_publisher_1->publish(slave_msg);

    // Create and publish master control message
    auto master_msg = buaa_rescue_robot_msgs::msg::ControlMessageMaster();
    master_control_topic_publisher->publish(master_msg);
}

void MainWindow::on_transButton_clicked()
{
    // Create and publish joint space message
    auto joint_msg = std_msgs::msg::Float64MultiArray();
    for (const auto &control : thetaControls)
    {
        joint_msg.data.push_back(control->value());
    }
    joint_space_topic_publisher->publish(joint_msg);
}

void MainWindow::updateSensorsMessageDisplay_1(const buaa_rescue_robot_msgs::msg::SensorsMessageRobomaster::SharedPtr msg)
{
    QStringList list;
    for (const auto &position : msg->snake_motor_encorder_position)
    {
        list << QString::number(position);
    }
    SensorsMessageDisplay_1->setStringList(list);
}

void MainWindow::updateSensorsMessageDisplay_3(const buaa_rescue_robot_msgs::msg::SensorsMessageMasterDeviceElevator::SharedPtr msg)
{
    QStringList list;
    list << QString::number(msg->elevator_counter)
         << QString::number(msg->lower_encorder)
         << QString::number(msg->upper_encorder);
    SensorsMessageDisplay_3->setStringList(list);
}

void MainWindow::updateSensorsMessageDisplay_4(const buaa_rescue_robot_msgs::msg::SensorsMessageMasterDevicePullPushSensors::SharedPtr msg)
{
    QStringList list;
    for (const auto &sensor : msg->pull_push_sensors)
    {
        list << QString::number(sensor);
    }
    SensorsMessageDisplay_4->setStringList(list);
}

void MainWindow::updateSensorsMessageDisplay_5(const buaa_rescue_robot_msgs::msg::SensorsMessageMasterDevicePullPushSensors::SharedPtr msg)
{
    QStringList list;
    for (const auto &sensor : msg->pull_push_sensors)
    {
        list << QString::number(sensor);
    }
    SensorsMessageDisplay_5->setStringList(list);
}

void MainWindow::updateSensorsMessageDisplay_6(const buaa_rescue_robot_msgs::msg::SensorsMessageRobomaster::SharedPtr msg)
{
    QStringList list;
    for (const auto &position : msg->snake_motor_encorder_position)
    {
        list << QString::number(position);
    }
    SensorsMessageDisplay_6->setStringList(list);
}

void MainWindow::updateSlaveControlIndicator1(const buaa_rescue_robot_msgs::msg::ControlMessageSlave::SharedPtr msg)
{
    for (size_t i = 0; i < speedControls_robomaster1.size(); ++i)
    {
        speedControls_robomaster1[i]->setValue(msg->snake_speed_control_array[i]);
        positionControls_robomaster1[i]->setValue(msg->snake_position_control_array[i]);
    }
    ui->robomaster1_mode->setValue(msg->robomaster_mode);
}
