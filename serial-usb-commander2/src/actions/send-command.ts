import { action, KeyDownEvent, SingletonAction } from "@elgato/streamdeck";
import { SerialPort } from "serialport";

@action({ UUID: "com.butzy79.serial-usb-commander2.send" })
export class SendSerialCommand extends SingletonAction<SerialSettings> {

	override async onKeyDown(ev: KeyDownEvent<SerialSettings>): Promise<void> {

		const command = ev.payload.settings.command ?? "ON";

		console.log("KEY PRESSED");
		console.log("COMMAND:", command);

		const port = new SerialPort({
			path: "COM5",
			baudRate: 115200
		});

		port.on("open", () => {
			console.log("SERIAL OPEN");
		});

		port.on("error", (err) => {
			console.log("SERIAL ERROR:", err.message);
		});

		await ev.action.showOk();
	}
}

type SerialSettings = {
	command?: string;
};