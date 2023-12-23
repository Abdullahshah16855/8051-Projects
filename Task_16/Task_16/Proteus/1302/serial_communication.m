s = serial('COM11');
set(s,'BaudRate',9600);
set(s,'Parity','none');
set(s,'DataBits',8);
set(s,'StopBit',1);
set(s,'TimeOut',1);
set(s,'Terminator','CR');
fopen(s);
fprintf('Enter your choice as below:\n');
fprintf('1. Appliance 1 on/off \t 2. Appliance 2 on/off\n3. Appliance 3 on/off \t 4. Appliance 4 on/off\n5. Get Status \t 6. Exit\n');
while(1)
    a = input('What is your choice?');
    if (a==1)
        fprintf(s,'1');
    elseif(a==2)
        fprintf(s,'2');
    elseif(a==3)
        fprintf(s,'3');
    elseif(a==4)
        fprintf(s,'4');
    elseif(a==5)
       fprintf(s,'5');
       b = fgets(s);
       c = hexToBinaryVector(b,4);
       
       %displaying the status of Appliances
       fprintf('Applicance 1 : ');
       if(c(1)==0)
            fprintf('on\n');
       else
           fprintf('off\n');
       end
       fprintf('Applicance 2 : ');
       if(c(2)==0)
            fprintf('on\n');
       else
           fprintf('off\n');
       end
       fprintf('Applicance 3 : ');
       if(c(3)==0)
            fprintf('on\n');
       else
           fprintf('off\n');
       end
       fprintf('Applicance 4 : ');
       if(c(4)==0)
            fprintf('on\n');
       else
           fprintf('off\n');
       end
    elseif(a==6)
        break;
    end    
end
fclose(s);
clc