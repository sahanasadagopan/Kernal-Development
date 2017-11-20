/**
 * @credits:http://derekmolloy.ie/kernel-gpio-programming-buttons-and-leds/
 * @file   led.c
 * @author Sahana Sadagopan
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>       
#include <linux/kobject.h>    
#include <linux/kthread.h> 
#include <linux/delay.h>   
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAHANA SADAGOPAN");
MODULE_DESCRIPTION("A simple Linux LED driver for the BBB");
MODULE_VERSION("0.1");
/***********Kernel Timer added**********************/
static struct timer_list kern_timer;
/*************GPIO pin for the MOdule************/
static unsigned int gpioLED = 53;

/***************Changing Duty Cycle**********************/
static unsigned int dutyCycle = 50;
module_param(dutyCycle,uint,S_IRUGO);
MODULE_PARM_DESC(blinkPeriod, " LED duty cycle in Percentage (min=0, default=50, max=100)");

/********************Blinkperiod*************************/
 /* Blink Period is the frequency at which the LED glows*/
static unsigned int blinkPeriod = 1000;     ///< The blink period in ms
module_param(blinkPeriod, uint, S_IRUGO);   ///< Param desc. S_IRUGO can be read/not changed
MODULE_PARM_DESC(blinkPeriod, " LED blink period in ms (min=1, default=1000, max=10000)");

/*Name of LED*/
static char ledName[7] = "led01";         
static bool ledOn = 0;                    
enum modes { OFF=0, ON=1, FLASH=2 };      
 /*Default MOde of LED FLashing*/
static enum modes mode = FLASH;
module_param(mode,uint,S_IRUGO);
MODULE_PARM_DESC(mode, " LED Mode)");

/*
* @func:Used to show the state of  the mode*
* @params: Kobject,kobj attribute and the buf where the value is stores
*/
static ssize_t mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
      if(mode==OFF){
         printk("LED OFF\n");
         return sprintf(buf, "off\n");
      }
      if(mode==ON){
         printk("LED ON\n");
         return sprintf(buf, "on\n");
      }
      if(mode==FLASH){
         printk("LED FLASH\n");
         return sprintf(buf, "flash\n");
      }
}
 /*
* @func:Used to save or write the state of  the mode*
* @params: Kobject,kobj attribute and the buf where the value is stores and a count value to keep track of what all to compare
*/
static ssize_t mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){
   if (strncmp(buf,"on",count-1)==0) { mode = ON; }  
   else if (strncmp(buf,"off",count-1)==0) { mode = OFF; }
   else if (strncmp(buf,"flash",count-1)==0) { mode = FLASH; }
   return count;
}
 
 /*
* @func:Used to show the state of  the period
* @params: Kobject,kobj attribute and the buf where the value is stores 
*/
static ssize_t period_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf){
   return sprintf(buf, "%d\n", blinkPeriod);
}
 
  /*
* @func:Used to save or write the state of  the frequency of led blinking*
* @params: Kobject,kobj attribute and the buf where the value is stores 
*/
static ssize_t period_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count){
   unsigned int period;                     
   sscanf(buf, "%du", &period);             
   if ((period>1)&&(period<=10000)){        
      blinkPeriod = period;               
   }
   return period;
}
 /*
* @func:Used to save or write the state of  the duty cycle*
* @params: Kobject,kobj attribute and the buf where the value is stores 
*/
static ssize_t duty_store(struct kobject *obj,struct kobj_attribute *attr,const char *buf,size_t count){
   unsigned int duty;
   sscanf(buf,"%d",&duty);
   if(duty>0 && duty<100){
      dutyCycle=duty;
      
   }
}


 /*
* @func:Used to show of  the duty cycle currently by default its 50*
* @params: Kobject,kobj attribute and the buf where the value is stores 
*/

static ssize_t duty_show(struct kobject *kobj, struct kobj_attribute *attr, const char *buf){
   return sprintf(buf,"%d\n",dutyCycle);
}

static struct kobj_attribute period_attr = __ATTR(blinkPeriod, 0664, period_show, period_store);
static struct kobj_attribute mode_attr = __ATTR(mode, 0664, mode_show, mode_store);
static struct kobj_attribute duty_attr = __ATTR(dutyCycle, 0664, duty_show, duty_store);

static struct attribute *led_attrs[] = {
   &period_attr.attr,                       // The period of LED 
   &mode_attr.attr,                         // LED state
   &duty_attr.attr,                       //Mode 
   NULL,
};
 

static struct attribute_group attr_group = {
   .attrs = led_attrs,                      // The attributes array defined just above
};
 
static struct kobject *kobj;            /// The pointer to the kobject
//static struct task_struct *task;  
 

void kern_timer_callback(unsigned long data){
   printk(KERN_INFO "MOdule running \n");
   //while(!kthread_should_stop()){           
     // set_current_state(TASK_RUNNING);
      if (mode==FLASH) ledOn = !ledOn;      // Invert the LED state
      else if (mode==ON) ledOn = true;
      else ledOn = false;
      gpio_set_value(gpioLED, ledOn);       // Use the LED state to light/turn off the LED
      //set_current_state(TASK_INTERRUPTIBLE);
      int err_check;
      err_check=mod_timer(&kern_timer,jiffies+msecs_to_jiffies((blinkPeriod*dutyCycle)/100));
      //msleep(blinkPeriod/2);                // millisecond sleep for half of the period
      if(dutyCycle){
         blinkPeriod =( blinkPeriod*(dutyCycle/100));
     //}
      //int err_check;
      //err_check=mod_timer(&kern_timer,jiffies+msecs_to_jiffies((blinkPeriod*dutyCycle)/100));
   }
   printk(KERN_INFO "The MOdule got all its values \n");
   return 0;
}
 /************************The Init Module that gets loaded on when first called**************************************************/

static int __init LED_init(void){
   int result = 0;
 
   printk(KERN_INFO "Initializing the LED\n");
   sprintf(ledName, "led%d", gpioLED);      // Create the gpio115 name for /sys/ebb/led49
 
   kobj = kobject_create_and_add("LED_Driver", kernel_kobj->parent); // kernel_kobj points to /sys/kernel
   if(!kobj){
      printk(KERN_ALERT "failed to create kobject\n");
      return -ENOMEM;
   }
   // add the attributes to /sys/ebb/ -- for example, /sys/ebb/led49/ledOn
   result = sysfs_create_group(kobj, &attr_group);
   if(result) {
      printk(KERN_ALERT "failed to create sysfs group\n");
      kobject_put(kobj);                // clean up -- remove the kobject sysfs entry
      return result;
   }
   ledOn = true;
   gpio_request(gpioLED, "sysfs");          // gpioLED is 49 by default, request it
   gpio_direction_output(gpioLED, ledOn);   // Set the gpio to be in output mode and turn on
   gpio_export(gpioLED, false);  // causes gpio49 to appear in /sys/class/gpio
                                 // the second argument prevents the direction from being changed
   
   setup_timer( &kern_timer ,kern_timer_callback,0);
   int err_check;
	err_check=mod_timer(&kern_timer,jiffies+msecs_to_jiffies(500));
	if(err_check){
		printk("Error in timer");
	}
  /* task = kthread_run(flash, NULL, "LED_flash_thread");  // Start the LED flashing thread
   if(IS_ERR(task)){                                     // Kthread name is LED_flash_thread
      printk(KERN_ALERT "failed to create the task\n");
      return PTR_ERR(task);
   }*/
   
   return result;
}
 
/*****************************Exit Module that would unload the module*************************************/
static void __exit LED_exit(void){
   kthread_stop(task);                      // Stop the LED flashing thread
   kobject_put(kobj);                   // clean up -- remove the kobject sysfs entry
   gpio_set_value(gpioLED, 0);              // Turn the LED off, indicates device was unloaded
   gpio_unexport(gpioLED);                  // Unexport the Button GPIO
   gpio_free(gpioLED);                      // Free the LED GPIO
   printk(KERN_INFO "LED Driver is OFF\n");
   int ret;
	ret = del_timer(&kern_timer);
	if(ret){
		printk("timer deleted");
	}
}
 

module_init(LED_init);
module_exit(LED_exit);
