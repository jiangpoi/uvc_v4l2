#include <linux/atomic.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <linux/wait.h>
#include <linux/version.h>
#include <asm/unaligned.h>
#include <media/v4l2-common.h>
#include <media/v4l2-ioctl.h>

//F:\学习\学习笔记\linux相关\linux驱动相关\v4l2\my_uvc\myuvc.c

struct video_device *myuvc_vdev;

/*A2查询性能*/
static int myuvc_vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *cap)
{
	return 0;
}

/*A3枚举所有支持的格式*/
static int myuvc_vidioc_enum_fmt_vid_cap(struct file *file, void  *priv,
					struct v4l2_fmtdesc *f)
{
	return 0;
}

/*A4获得当前使用的格式*/
static int myuvc_vidioc_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	return (0);
}

/*A5尝试设置指定的格式*/
static int myuvc_vidioc_try_fmt_vid_cap(struct file *file, void *priv,
			struct v4l2_format *f)
{
    return 0;
}

/*A6设置格式*/
static int myuvc_vidioc_s_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
    return 0;
}

/*A7申请缓冲区头部*/
static int myuvc_vidioc_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *p)
{
	return 0;
}

/*A8查询缓冲区，获得缓冲区的信息*/
static int myuvc_vidioc_querybuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	return 0;
}


/*A9将缓冲区映射到用户空间，真正的分配缓冲区空间*/
static int myuvc_mmap(struct file *file, struct vm_area_struct *vma)
{
	return 0;
}


/*A10将缓冲区放入队列末尾*/
static int myuvc_vidioc_qbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	return 0;
}

/*A11开始stream*/
static int myuvc_vidioc_streamon(struct file *file, void *priv, enum v4l2_buf_type i)
{
	return 0;
}


/*A12 应用程序调用poll或者select来确定是否有数据 */
static unsigned int myuvc_poll(struct file *file, struct poll_table_struct *wait)
{
	return 0;
}


/*A13调用poll后确定有数据调用从头部拿出缓冲区*/
static int myuvc_vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	return 0;
}

/*A14之前通过mmap已经得到了对应的应用空间地址，可以直接读取*/
/*A15再次掉用qbuf*/
/*A16再次调用poll*/


/*A17如果需要退出，则调用stream_off,停止stream*/
static int myuvc_vidioc_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
    return 0;
}

static void myuvc_release(struct video_device *vdev)
{
	return;
}

/*A1打开设备描述符*/
static int myuvc_open(struct file *file)
{
	return 0;
}
/*A18关闭*/
static int myuvc_close(struct file *file)
{
    
	return 0;
}



static struct usb_device_id myuvc_ids[] = {
/* Generic USB Video Class */
{ USB_INTERFACE_INFO(USB_CLASS_VIDEO, 1, 0) },//VideoControlq，其实VC包含了VS
{ USB_INTERFACE_INFO(USB_CLASS_VIDEO, 2, 0) },//videoStreaming
{}

};

static const struct v4l2_ioctl_ops myuvc_ioctl_ops = {
        
        .vidioc_querycap      = myuvc_vidioc_querycap,
        .vidioc_enum_fmt_vid_cap  = myuvc_vidioc_enum_fmt_vid_cap,
        .vidioc_g_fmt_vid_cap     = myuvc_vidioc_g_fmt_vid_cap,
        .vidioc_try_fmt_vid_cap   = myuvc_vidioc_try_fmt_vid_cap,
        .vidioc_s_fmt_vid_cap     = myuvc_vidioc_s_fmt_vid_cap,
        .vidioc_reqbufs       = myuvc_vidioc_reqbufs,
        .vidioc_querybuf      = myuvc_vidioc_querybuf,
        .vidioc_qbuf          = myuvc_vidioc_qbuf,
        .vidioc_dqbuf         = myuvc_vidioc_dqbuf,
        .vidioc_streamon      = myuvc_vidioc_streamon,
        .vidioc_streamoff     = myuvc_vidioc_streamoff,   
};

static const struct v4l2_file_operations myuvc_fops = {
	.owner		= THIS_MODULE,
    .open       = myuvc_open,
    .release    = myuvc_close,
    .mmap       = myuvc_mmap,
    .ioctl      = video_ioctl2, /* V4L2 ioctl handler */
    .poll       = myuvc_poll,
};


static int myuvc_probe(struct usb_interface *intf,
		     const struct usb_device_id *id)
{
	int cnt = 0;
	/*
	struct usb_device *dev = interface_to_usbdev(intf);//获取usb_device即设备描述结构体
	struct usb_device_descriptor *descriptor = &(dev->descriptor);
	struct usb_config_descriptor *config = &dev->config->desc;
	struct usb_host_config *hostconfig=  dev->config;
	struct usb_interface_assoc_descriptor * intf_assoc=NULL;
	struct usb_interface_descriptor	*interface=NULL;
	struct usb_endpoint_descriptor * endpoint=NULL;

	unsigned char *buffer;
	int buflen = 0;
	int desc_len = 0;//自定义设置描述符的长度
	int desc_n = 0;//第几个自定义设置描述符
	*/
	printk("probe_times= %d\n",cnt++);
	/*分配一个video_device结构体*/
	myuvc_vdev = video_device_alloc();
	/*设置*/
    myuvc_vdev->release = myuvc_release;
    myuvc_vdev->fops    = &myuvc_fops;
    myuvc_vdev->ioctl_ops = &myuvc_ioctl_ops;
	

	/*注册*/
	if(cnt == 2)
	{
		video_register_device(myuvc_vdev, VFL_TYPE_GRABBER, -1);
	}
	return 0;
}

static void myuvc_disconnect(struct usb_interface *intf)
{
	int cnt=0;
	printk("disconnect=%d\n",cnt++);
	 if (cnt == 2)
    {
        video_unregister_device(myuvc_vdev);
        video_device_release(myuvc_vdev);
    }
    
	return;
}


static struct usb_driver myuvc_driver = {
		.name		= "myuvc",
		.probe		= myuvc_probe,
		.disconnect	= myuvc_disconnect,
		.id_table	= myuvc_ids,
};


static int myuvc_init(void)
{
 /*分配一个usb结构体注册*/
	usb_register(&myuvc_driver);
 	return 0;
}

static void myuvc_exit(void)
{
	usb_deregister(&myuvc_driver);
	return ;
}


module_init(myuvc_init);
module_exit(myuvc_exit);
MODULE_LICENSE("GPL");






