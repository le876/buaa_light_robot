#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QApplication>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QListView>
#include <QMenuBar>
#include <QPushButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QStringListModel>
#include <QKeyEvent>
#include <rclcpp/rclcpp.hpp>
#include <buaa_rescue_robot_msgs/msg/control_message_slave.hpp>
#include <buaa_rescue_robot_msgs/msg/control_message_master.hpp>
#include <buaa_rescue_robot_msgs/msg/sensors_message_robomaster.hpp>
#include <buaa_rescue_robot_msgs/msg/sensors_message_master_device_elevator.hpp>
#include <buaa_rescue_robot_msgs/msg/sensors_message_master_device_pull_push_sensors.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateSensorsMessageDisplay_1(const buaa_rescue_robot_msgs::msg::SensorsMessageRobomaster::SharedPtr msg);
    void updateSensorsMessageDisplay_3(const buaa_rescue_robot_msgs::msg::SensorsMessageMasterDeviceElevator::SharedPtr msg);
    void updateSensorsMessageDisplay_4(const buaa_rescue_robot_msgs::msg::SensorsMessageMasterDevicePullPushSensors::SharedPtr msg);
    void updateSensorsMessageDisplay_5(const buaa_rescue_robot_msgs::msg::SensorsMessageMasterDevicePullPushSensors::SharedPtr msg);
    void updateSensorsMessageDisplay_6(const buaa_rescue_robot_msgs::msg::SensorsMessageRobomaster::SharedPtr msg);
    void updateSlaveControlIndicator1(const buaa_rescue_robot_msgs::msg::ControlMessageSlave::SharedPtr msg);

private slots:
    void on_publishButton_clicked();
    void on_transButton_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<rclcpp::Node> node;
    rclcpp::Publisher<buaa_rescue_robot_msgs::msg::ControlMessageSlave>::SharedPtr slave_control_topic_publisher_1;
    rclcpp::Publisher<buaa_rescue_robot_msgs::msg::ControlMessageMaster>::SharedPtr master_control_topic_publisher;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr joint_space_topic_publisher;

    QStringListModel *SensorsMessageDisplay_1;
    QStringListModel *SensorsMessageDisplay_3;
    QStringListModel *SensorsMessageDisplay_4;
    QStringListModel *SensorsMessageDisplay_5;
    QStringListModel *SensorsMessageDisplay_6;

    std::vector<QDoubleSpinBox *> thetaControls;
    std::vector<QSpinBox *> speedControls_robomaster1;
    std::vector<QSpinBox *> positionControls_robomaster1;
};
#endif // MAINWINDOW_H
