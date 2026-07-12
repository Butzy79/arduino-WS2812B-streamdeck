import { action, KeyDownEvent, SingletonAction } from "@elgato/streamdeck";
import { SerialPort } from "serialport";

@action({ UUID: "com.butzy79.serial-usb-commander2.send" })
export class SendSerialCommand extends SingletonAction<SerialSettings> {

	override async onKeyDown(ev: KeyDownEvent<SerialSettings>): Promise<void> {

		const command = ev.payload.settings.command ?? "ON";

		console.log("USB SERIAL COMMAND:", command);

		const port = new SerialPort({
			path: "COM7",
			baudRate: 115200
		});

		port.on("open", () => {
			port.write(command + "\n", () => {
				console.log("Sent:", command);

				port.close();
			});
		});

		await ev.action.showOk();
	}
}

type SerialSettings = {
	command?: string;
};